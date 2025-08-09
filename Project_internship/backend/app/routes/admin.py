from flask import Blueprint, request, jsonify
from flask_jwt_extended import jwt_required, get_jwt_identity
from app.models.user import User
from app.models.class_model import Class, Schedule
from app.models.teacher import Teacher
from app.models.student import Student
from app.models.attendance import Attendance
from app import db

admin_bp = Blueprint('admin', __name__)

def admin_required(fn):
    @jwt_required()
    def wrapper(*args, **kwargs):
        user_id = get_jwt_identity()
        user = User.query.get(user_id)
        
        if not user or user.role != 'admin':
            return jsonify({'error': 'Admin access required'}), 403
        
        return fn(*args, **kwargs)
    return wrapper

@admin_bp.route('/classes', methods=['POST'])
@admin_required
def create_class():
    try:
        data = request.get_json()
        
        new_class = Class(
            name=data['name'],
            section=data.get('section'),
            academic_year=data['academic_year'],
            teacher_id=data.get('teacher_id'),
            room_number=data.get('room_number'),
            capacity=data.get('capacity')
        )
        
        db.session.add(new_class)
        db.session.commit()
        
        return jsonify(new_class.to_dict()), 201
    
    except Exception as e:
        db.session.rollback()
        return jsonify({'error': str(e)}), 500

@admin_bp.route('/classes/<int:class_id>/schedule', methods=['POST'])
@admin_required
def create_schedule(class_id):
    try:
        data = request.get_json()
        
        new_schedule = Schedule(
            class_id=class_id,
            day_of_week=data['day_of_week'],
            start_time=data['start_time'],
            end_time=data['end_time']
        )
        
        db.session.add(new_schedule)
        db.session.commit()
        
        return jsonify(new_schedule.to_dict()), 201
    
    except Exception as e:
        db.session.rollback()
        return jsonify({'error': str(e)}), 500

@admin_bp.route('/teachers', methods=['POST'])
@admin_required
def create_teacher():
    try:
        data = request.get_json()
        
        # Create user account
        user = User(
            username=data['username'],
            email=data['email'],
            role='teacher'
        )
        user.set_password(data['password'])
        db.session.add(user)
        db.session.flush()  # Get user ID without committing
        
        # Create teacher profile
        teacher = Teacher(
            user_id=user.id,
            first_name=data['first_name'],
            last_name=data['last_name'],
            email=data['email'],
            phone_number=data.get('phone_number'),
            department=data.get('department'),
            qualification=data.get('qualification'),
            experience_years=data.get('experience_years')
        )
        
        db.session.add(teacher)
        db.session.commit()
        
        return jsonify(teacher.to_dict()), 201
    
    except Exception as e:
        db.session.rollback()
        return jsonify({'error': str(e)}), 500

@admin_bp.route('/dashboard', methods=['GET'])
@admin_required
def get_dashboard_data():
    try:
        # Get total counts
        total_students = Student.query.count()
        total_teachers = Teacher.query.count()
        total_classes = Class.query.count()
        
        # Get recent attendance records
        recent_attendance = Attendance.query.order_by(
            Attendance.created_at.desc()
        ).limit(10).all()
        
        return jsonify({
            'total_students': total_students,
            'total_teachers': total_teachers,
            'total_classes': total_classes,
            'recent_attendance': [record.to_dict() for record in recent_attendance]
        }), 200
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500 