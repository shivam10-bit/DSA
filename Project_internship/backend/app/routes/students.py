from flask import Blueprint, request, jsonify
from flask_jwt_extended import jwt_required, get_jwt_identity
from app.models.student import Student
from app.models.user import User
from app.services.face_recognition_service import FaceRecognitionService
from app import db

students_bp = Blueprint('students', __name__)
face_recognition_service = FaceRecognitionService()

@students_bp.route('/', methods=['POST'])
@jwt_required()
def create_student():
    try:
        data = request.get_json()
        
        # Create user account
        user = User(
            username=data['username'],
            email=data['email'],
            role='student'
        )
        user.set_password(data['password'])
        db.session.add(user)
        db.session.flush()  # Get user ID without committing
        
        # Create student profile
        student = Student(
            user_id=user.id,
            roll_number=data['roll_number'],
            first_name=data['first_name'],
            last_name=data['last_name'],
            date_of_birth=data['date_of_birth'],
            gender=data['gender'],
            address=data.get('address'),
            phone_number=data.get('phone_number'),
            emergency_contact=data.get('emergency_contact'),
            class_id=data.get('class_id')
        )
        
        db.session.add(student)
        db.session.commit()
        
        return jsonify(student.to_dict()), 201
    
    except Exception as e:
        db.session.rollback()
        return jsonify({'error': str(e)}), 500

@students_bp.route('/<int:student_id>', methods=['GET'])
@jwt_required()
def get_student(student_id):
    try:
        student = Student.query.get(student_id)
        if not student:
            return jsonify({'error': 'Student not found'}), 404
        
        return jsonify(student.to_dict()), 200
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@students_bp.route('/<int:student_id>', methods=['PUT'])
@jwt_required()
def update_student(student_id):
    try:
        student = Student.query.get(student_id)
        if not student:
            return jsonify({'error': 'Student not found'}), 404
        
        data = request.get_json()
        
        # Update student information
        for key, value in data.items():
            if hasattr(student, key):
                setattr(student, key, value)
        
        db.session.commit()
        return jsonify(student.to_dict()), 200
    
    except Exception as e:
        db.session.rollback()
        return jsonify({'error': str(e)}), 500

@students_bp.route('/<int:student_id>/face', methods=['POST'])
@jwt_required()
def register_face(student_id):
    try:
        student = Student.query.get(student_id)
        if not student:
            return jsonify({'error': 'Student not found'}), 404
        
        data = request.get_json()
        image_data = data.get('image')
        
        if not image_data:
            return jsonify({'error': 'Image data required'}), 400
        
        success = face_recognition_service.register_face(student_id, image_data)
        
        if success:
            return jsonify({'message': 'Face registered successfully'}), 200
        else:
            return jsonify({'error': 'Failed to register face'}), 400
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@students_bp.route('/class/<int:class_id>', methods=['GET'])
@jwt_required()
def get_class_students(class_id):
    try:
        students = Student.query.filter_by(class_id=class_id).all()
        return jsonify([student.to_dict() for student in students]), 200
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500 