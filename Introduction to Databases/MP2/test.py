Python 3.8.5 (tags/v3.8.5:580fbb0, Jul 20 2020, 15:57:54) [MSC v.1924 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> import os
>>> os.chdir(r'C:\Users\asus\Desktop\Programming Test')
>>> from task import *
>>> connection = connect()
>>> cur = connection.cursor()
>>> 
>>> create_tables(cur)
>>> 
>>> insert_data(cur)
>>> insert_student(cur, 1000000, 'Krydom', 13, 'IIIS')
>>> insert_course(cur, 100, 'Database System', 3, 3, 3, '<Req></Req>')
>>> delete_student(cur, 1000000)
>>> delete_course(cur,100)
>>> 
>>> count_course_students(cur, 101)
1
>>> count_course_students(cur, 102)
0
>>> 
>>> check_requirement(cur, 1000113, 102)
True
>>> check_requirement(cur, 1000214, 102)
False
>>> check_requirement(cur, 1000214, 101)
True
>>> 
>>> register_student(cur, 1000214, 102)
The student can not meet the course requirements.
False
>>> register_student(cur, 1000214, 101)
Successfully Registered the student to the course.
True
>>> register_student(cur, 1002079, 101)
Successfully Registered the student to the course.
True
>>> register_student(cur, 1002098, 101)
Successfully Registered the student to the course.
True
>>> register_student(cur, 1003342, 101)
The course has no remainCapacity. Failed to register.
False
>>> 
>>> remove_student(cur, 1002098, 101)
>>> 
>>> update_capacity(cur, 101, 2)
>>> update_capacity(cur, 101, 3)
>>> 
>>> register_student(cur, 1000113, 102)
Successfully Registered the student to the course.
True
>>> retrieve_attended(cur, 1000113)
['C++', 'Introduction to CS']
>>> retrieve_attended(cur, 1000214)
['Introduction to CS']
>>> retrieve_attended(cur, 1002098)
[]
>>> 
>>> update_grade(cur, 1000214, 101, 60)
>>> update_grade(cur, 1002079, 101, 59)
>>> 
>>> retrieve_failure(cur)
( Daisy White , Introduction to CS )
( Wade Williams , C++ )
>>> 
>>> compute_gpa(cur, 1000113)
Decimal('2.000000')
>>> 
>>> course_avg(cur, 101)
72
>>> 