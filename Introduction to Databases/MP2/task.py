import pyodbc


# connect to sql server
def connect(
        DRIVER='SQL Server Native Client 11.0',
        SERVER='LAPTOP-9135239P',
        DATABASE='mp2',
        USERNAME='sa',
        PASSWORD='123456'):
    connection = pyodbc.connect(
        f'DRIVER={DRIVER};SERVER={SERVER};DATABASE={DATABASE};UID={USERNAME};PWD={PASSWORD}'
    )
    return connection


# create required tables
def create_tables(cursor):
    sql = """
        CREATE TABLE student (
            ID INT PRIMARY KEY NOT NULL,
            Name VARCHAR(255) NOT NULL,
            Age INT NOT NULL,
            Dept VARCHAR(255) NOT NULL
        );
        CREATE TABLE course (
            CourseID INT PRIMARY KEY NOT NULL,
            CourseName VARCHAR(255) NOT NULL,
            Capacity INT NOT NULL,
            RemainCapacity INT NOT NULL,
            CreditHours INT NOT NULL,
            Requirement XML NOT NULL
        );
        CREATE TABLE registration (
            StudentID INT FOREIGN KEY REFERENCES student(ID) NOT NULL,
            CourseID INT FOREIGN KEY REFERENCES course(CourseID) NOT NULL,
            Grade INT NOT NULL DEFAULT 0
        );
    """
    cursor.execute(sql)
    cursor.commit()


# Insert data
def insert_data(cursor):
    cursor.execute("""
    INSERT INTO student
    VALUES
        (1000113, 'Wade Williams', 20, 'CS'),
        (1000214, 'Dave Harris',   20, 'CS'),
        (1002098, 'Ivan Scott',    18, 'EE'),
        (1002079, 'Daisy White',   21, 'EE'),
        (1003342, 'Lucy Clark',    21, 'CS');
    INSERT INTO course
    VALUES
        (101, 'Introduction to CS', 4, 3, 3, '<Req></Req>'),
        (102, 'C++',                3, 3, 3, '<Req><PrerequisiteCourse>101</PrerequisiteCourse></Req>');
    INSERT INTO registration
    VALUES
        (1000113, 101, 99);
    """)
    cursor.commit()


# Insert a student
def insert_student(cursor, ID, name, age, dept):
    cursor.execute("""
    INSERT INTO student VALUES (?,?,?,?)
    """, ID, name, age, dept)
    cursor.commit()


# Insert a course
def insert_course(cursor, ID, name, capacity, remain_capacity, credit_hour, requirement):
    cursor.execute("""
    INSERT INTO course VALUES (?,?,?,?,?,?)
    """, ID, name, capacity, remain_capacity, credit_hour, requirement)
    cursor.commit()


# Delete a student
def delete_student(cursor, ID):
    cursor.execute("""
    DELETE FROM student WHERE ID = ?
    """, ID)
    cursor.commit()


# Delete a course
def delete_course(cursor, ID):
    cursor.execute("""
    DELETE FROM course WHERE CourseID = ?
    """, ID)
    cursor.commit()


# Look up the number of students enrolled in a course
def count_course_students(cursor, course_id):
    cursor.execute("""
    SELECT COUNT(StudentID) FROM registration
    WHERE CourseID = ?;
    """, (course_id,))
    res = cursor.fetchone()
    if res:
        return res[0]
    else:
        return None


# Check whether a student satisfies the requirement of a course
def check_requirement(cursor, student_id, course_id):

    # Find the prerequisite course
    cursor.execute("""
    SELECT Requirement.value('(/Req/PrerequisiteCourse)[1]','int') as CourseID
    FROM course
    WHERE CourseID=?;
    """, (course_id,))
    row = cursor.fetchone()
    pre_courseID = row.CourseID

    # If the course has no prerequisite course, everyone can take it
    if pre_courseID is None:
        return True

    # Find the student's grade of the prerequisite course
    cursor.execute("""
    SELECT grade FROM registration WHERE StudentID = ? AND CourseID = ?
    """, (student_id, pre_courseID))
    row = cursor.fetchone()

    # If the student has not taken the prerequisite course, he can not take this course
    if row is None:
        return False

    # If the student has not passed the prerequisite course, he can not take this course
    student_grade = row.grade
    if student_grade < 60:
        return False
    else:
        return True


# Register a student to a course, use transaction
def register_student(cursor, student_id, course_id):

    # check remains
    cursor.execute(
        """SELECT RemainCapacity as remain FROM course WHERE CourseID=?""", (course_id,))
    row = cursor.fetchone()

    # reject this operation if the course is already at capacity limit
    if row.remain <= 0:
        print("The course has no remainCapacity. Failed to register.")
        return False

    # reject this operation if the student cannot register due to unmet requirements
    if not check_requirement(cursor, student_id, course_id):
        print("The student can not meet the course requirements.")
        return False

    # Register a student to a course, use transaction
    cursor.execute("""
    BEGIN TRANSACTION
    INSERT INTO registration
    VALUES (?,?,0)
    UPDATE course SET RemainCapacity -= 1
    WHERE CourseID=?
    COMMIT TRANSACTION
    """, student_id, course_id, course_id)
    cursor.commit()
    print('Successfully Registered the student to the course.')
    return True


# Remove a student from a course (use transaction)
def remove_student(cursor, student_id, course_id):
    cursor.execute("""
        DECLARE @student_id INT
        DECLARE @course_id INT
        SET @student_id=?
        SET @course_id=?
        BEGIN TRANSACTION
        -- delete from registration
        DELETE TOP(1) FROM registration
        WHERE StudentID=@student_id AND CourseID=@course_id
        -- remaincapacity plus one
        UPDATE course SET RemainCapacity += 1
        WHERE CourseID = ?
        COMMIT TRANSACTION
    """, (student_id, course_id, course_id))
    cursor.commit()


# Update the capacity of a course, use transaction
# reject this operation if the number of students already enrolled exceeds the new capacity
def update_capacity(cursor, course_id, new_cap):
    enrolled = count_course_students(cursor, course_id)
    cursor.execute("""
    DECLARE @enrolled INT
    DECLARE @new_cap INT
    DECLARE @course_id INT
    SET @enrolled=?
    SET @course_id=?
    SET @new_cap=?
    BEGIN TRANSACTION
    IF @enrolled <= @new_cap
    UPDATE course SET Capacity = @new_cap, RemainCapacity = @new_cap - @enrolled
    WHERE CourseID=@course_id
    COMMIT TRANSACTION;
    """, (enrolled, course_id, new_cap))
    cursor.commit()


# Retrieve the list of courses a student have attended in the past
def retrieve_attended(cursor, student_id):
    cursor.execute("""
    SELECT DISTINCT CourseName as name FROM course
    JOIN registration ON course.CourseID = registration.CourseID
    WHERE StudentID=?
    """, (student_id,))
    rows = cursor.fetchall()
    names = []
    for row in rows:
        names.append(row.name)
    return names


# Retrieve all the course failure records
# all the <student, course> pair that the student failed to pass the course (grade < 60)
def retrieve_failure(cursor):
    cursor.execute("""
    SELECT Name, CourseName
    FROM registration
    JOIN course ON course.CourseID = registration.CourseID
    JOIN student ON student.ID = registration.StudentID
    WHERE registration.Grade < 60
    """)
    row = cursor.fetchone()
    while row:
        stu, cour = row
        print('(', stu, ',', cour, ')')
        row = cursor.fetchone()


# Update the grade of a student in a course
def update_grade(cursor, student_id, course_id, grade):
    cursor.execute("""
    UPDATE registration SET Grade=?
    WHERE CourseID=? AND StudentID=?
    """, (grade, course_id, student_id))
    cursor.commit()


# Compute the GPA of a student
def compute_gpa(cursor, student_id):
    cursor.execute("""
    SELECT
        AVG(
        (CASE
            WHEN Grade >= 93 AND Grade <= 100 THEN 4.0
            WHEN Grade >= 90 AND Grade <= 92 THEN 3.7
            WHEN Grade >= 87 AND Grade <= 89 THEN 3.3
            WHEN Grade >= 83 AND Grade <= 86 THEN 3.0
            WHEN Grade >= 80 AND Grade <= 82 THEN 2.7
            WHEN Grade >= 77 AND Grade <= 79 THEN 2.3
            WHEN Grade >= 73 AND Grade <= 76 THEN 2.0
            WHEN Grade >= 70 AND Grade <= 72 THEN 1.7
            WHEN Grade >= 67 AND Grade <= 69 THEN 1.3
            WHEN Grade >= 65 AND Grade <= 66 THEN 1.0
            ELSE 0.0
        END)
        ) GPA FROM registration
        WHERE StudentID = ?
    """, (student_id,))
    row = cursor.fetchone()
    return row.GPA


# Compute the average grade of students in a course
def course_avg(cursor, course_id):
    cursor.execute("""
    SELECT AVG(Grade) as grade FROM registration
    WHERE CourseID=?
    """, (course_id))
    row = cursor.fetchone()
    return row.grade
