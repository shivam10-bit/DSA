from datetime import datetime, time
from app.models.attendance import Attendance
from app.models.student import Student
from app.models.class import Class, Schedule
from app import db

class AttendanceService:
    def record_attendance(self, student_id, attendance_type, location=None):
        """Record attendance for a student"""
        try:
            today = datetime.now().date()
            current_time = datetime.now()
            
            # Get student's class schedule
            student = Student.query.get(student_id)
            if not student or not student.class_id:
                return False, "Student not found or not assigned to a class"
            
            class_schedule = Schedule.query.filter_by(
                class_id=student.class_id,
                day_of_week=current_time.weekday()
            ).first()
            
            if not class_schedule:
                return False, "No schedule found for today"
            
            # Check if attendance already exists for today
            existing_attendance = Attendance.query.filter_by(
                student_id=student_id,
                date=today
            ).first()
            
            if existing_attendance:
                # Update punch out time if it's not set
                if not existing_attendance.punch_out_time:
                    existing_attendance.punch_out_time = current_time
                    db.session.commit()
                    return True, "Punch out recorded successfully"
                return False, "Attendance already recorded for today"
            
            # Determine status based on class schedule
            class_start_time = datetime.combine(today, class_schedule.start_time)
            status = "late" if current_time > class_start_time else "present"
            
            # Create new attendance record
            new_attendance = Attendance(
                student_id=student_id,
                date=today,
                punch_in_time=current_time,
                status=status,
                attendance_type=attendance_type,
                location=location
            )
            
            db.session.add(new_attendance)
            db.session.commit()
            return True, "Attendance recorded successfully"
        
        except Exception as e:
            db.session.rollback()
            return False, f"Error recording attendance: {str(e)}"
    
    def get_student_attendance(self, student_id, start_date=None, end_date=None):
        """Get attendance records for a student"""
        try:
            query = Attendance.query.filter_by(student_id=student_id)
            
            if start_date:
                query = query.filter(Attendance.date >= start_date)
            if end_date:
                query = query.filter(Attendance.date <= end_date)
            
            attendance_records = query.order_by(Attendance.date.desc()).all()
            return [record.to_dict() for record in attendance_records]
        
        except Exception as e:
            return []
    
    def get_class_attendance(self, class_id, date):
        """Get attendance records for a class on a specific date"""
        try:
            students = Student.query.filter_by(class_id=class_id).all()
            student_ids = [student.id for student in students]
            
            attendance_records = Attendance.query.filter(
                Attendance.student_id.in_(student_ids),
                Attendance.date == date
            ).all()
            
            return [record.to_dict() for record in attendance_records]
        
        except Exception as e:
            return []
    
    def generate_attendance_report(self, class_id, start_date, end_date):
        """Generate attendance report for a class"""
        try:
            students = Student.query.filter_by(class_id=class_id).all()
            report = []
            
            for student in students:
                attendance_records = Attendance.query.filter(
                    Attendance.student_id == student.id,
                    Attendance.date >= start_date,
                    Attendance.date <= end_date
                ).all()
                
                total_days = (end_date - start_date).days + 1
                present_days = sum(1 for record in attendance_records if record.status == "present")
                late_days = sum(1 for record in attendance_records if record.status == "late")
                absent_days = total_days - present_days - late_days
                
                report.append({
                    'student_id': student.id,
                    'student_name': f"{student.first_name} {student.last_name}",
                    'roll_number': student.roll_number,
                    'total_days': total_days,
                    'present_days': present_days,
                    'late_days': late_days,
                    'absent_days': absent_days,
                    'attendance_percentage': (present_days / total_days * 100) if total_days > 0 else 0
                })
            
            return report
        
        except Exception as e:
            return [] 