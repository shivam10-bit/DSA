from flask import Blueprint, request, jsonify
from flask_jwt_extended import jwt_required, get_jwt_identity
from app.services.attendance_service import AttendanceService
from app.services.face_recognition_service import FaceRecognitionService
from app.models.user import User
from datetime import datetime

attendance_bp = Blueprint('attendance', __name__)
attendance_service = AttendanceService()
face_recognition_service = FaceRecognitionService()

@attendance_bp.route('/record', methods=['POST'])
@jwt_required()
def record_attendance():
    try:
        data = request.get_json()
        attendance_type = data.get('attendance_type', 'face')  # face, fingerprint, card
        location = data.get('location')
        
        if attendance_type == 'face':
            # Handle face recognition
            image_data = data.get('image')
            if not image_data:
                return jsonify({'error': 'Image data required for face recognition'}), 400
            
            student_id = face_recognition_service.recognize_face(image_data)
            if not student_id:
                return jsonify({'error': 'Face not recognized'}), 400
        
        elif attendance_type == 'fingerprint':
            # Handle fingerprint recognition
            fingerprint_id = data.get('fingerprint_id')
            if not fingerprint_id:
                return jsonify({'error': 'Fingerprint ID required'}), 400
            
            # TODO: Implement fingerprint recognition logic
            student_id = None  # Get student ID from fingerprint
        
        elif attendance_type == 'card':
            # Handle card-based attendance
            card_id = data.get('card_id')
            if not card_id:
                return jsonify({'error': 'Card ID required'}), 400
            
            # TODO: Implement card recognition logic
            student_id = None  # Get student ID from card
        
        else:
            return jsonify({'error': 'Invalid attendance type'}), 400
        
        if not student_id:
            return jsonify({'error': 'Student not found'}), 404
        
        success, message = attendance_service.record_attendance(
            student_id=student_id,
            attendance_type=attendance_type,
            location=location
        )
        
        if success:
            return jsonify({'message': message}), 200
        else:
            return jsonify({'error': message}), 400
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@attendance_bp.route('/student/<int:student_id>', methods=['GET'])
@jwt_required()
def get_student_attendance(student_id):
    try:
        start_date = request.args.get('start_date')
        end_date = request.args.get('end_date')
        
        if start_date:
            start_date = datetime.strptime(start_date, '%Y-%m-%d').date()
        if end_date:
            end_date = datetime.strptime(end_date, '%Y-%m-%d').date()
        
        attendance_records = attendance_service.get_student_attendance(
            student_id=student_id,
            start_date=start_date,
            end_date=end_date
        )
        
        return jsonify(attendance_records), 200
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@attendance_bp.route('/class/<int:class_id>', methods=['GET'])
@jwt_required()
def get_class_attendance(class_id):
    try:
        date_str = request.args.get('date')
        if not date_str:
            return jsonify({'error': 'Date parameter required'}), 400
        
        date = datetime.strptime(date_str, '%Y-%m-%d').date()
        attendance_records = attendance_service.get_class_attendance(
            class_id=class_id,
            date=date
        )
        
        return jsonify(attendance_records), 200
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@attendance_bp.route('/report/<int:class_id>', methods=['GET'])
@jwt_required()
def generate_attendance_report(class_id):
    try:
        start_date = request.args.get('start_date')
        end_date = request.args.get('end_date')
        
        if not start_date or not end_date:
            return jsonify({'error': 'Start date and end date parameters required'}), 400
        
        start_date = datetime.strptime(start_date, '%Y-%m-%d').date()
        end_date = datetime.strptime(end_date, '%Y-%m-%d').date()
        
        report = attendance_service.generate_attendance_report(
            class_id=class_id,
            start_date=start_date,
            end_date=end_date
        )
        
        return jsonify(report), 200
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500 