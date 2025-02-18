import psycopg2
from psycopg2 import Error
import shlex

def connect_to_db():
    return psycopg2.connect(
        user="postgres",
        password="postgres",
        host="127.0.0.1",
        port="5432",
        database="study"
    )

def get_student(student_id):
    try:
        with connect_to_db() as conn:
            with conn.cursor() as cur:
                cur.execute('SELECT * FROM students WHERE ids = %s', (student_id,))
                result = cur.fetchone()
                if result:
                    print(f"ID: {result[0]}, Имя: {result[1]}, Курс: {result[2]}")
                else:
                    print("Студент не найден")
    except Error as e:
        print(f"Ошибка при получении данных студента: {e}")

def get_discipline(course):
    try:
        with connect_to_db() as conn:
            with conn.cursor() as cur:
                cur.execute('''
                    SELECT * FROM disciplines 
                    WHERE nomk = %s 
                    ORDER BY dweek, nomp
                ''', (course,))
                results = cur.fetchall()
                if results:
                    for r in results:
                        print(f"ID: {r[0]}, Предмет: {r[1]}, День: {r[2]}, Пара: {r[3]}, Курс: {r[4]}")
                else:
                    print("Занятия не найдены")
    except Error as e:
        print(f"Ошибка при получении расписания: {e}")

def get_students(course):
    try:
        with connect_to_db() as conn:
            with conn.cursor() as cur:
                cur.execute('''
                    SELECT * FROM students 
                    WHERE nomk = %s 
                    ORDER BY name_st
                ''', (course,))
                results = cur.fetchall()
                if results:
                    for r in results:
                        print(f"ID: {r[0]}, Имя: {r[1]}, Курс: {r[2]}")
                else:
                    print("Студенты не найдены")
    except Error as e:
        print(f"Ошибка при получении списка студентов: {e}")

def get_disciplines():
    try:
        with connect_to_db() as conn:
            with conn.cursor() as cur:
                cur.execute('SELECT * FROM disciplines ORDER BY dweek, nomp, nomk')
                results = cur.fetchall()
                if results:
                    for r in results:
                        print(f"ID: {r[0]}, Предмет: {r[1]}, День: {r[2]}, Пара: {r[3]}, Курс: {r[4]}")
                else:
                    print("Расписание пусто")
    except Error as e:
        print(f"Ошибка при получении расписания: {e}")

def put_student(name, course):
    try:
        with connect_to_db() as conn:
            with conn.cursor() as cur:
                cur.execute('SELECT MAX(ids) FROM students')
                max_id = cur.fetchone()[0]
                new_id = 1 if max_id is None else max_id + 1
                
                cur.execute('''
                    INSERT INTO students (ids, name_st, nomk) 
                    VALUES (%s, %s, %s)
                ''', (new_id, name, course))
                conn.commit()
                print(f"Студент успешно добавлен с ID: {new_id}")
    except Error as e:
        print(f"Ошибка при добавлении студента: {e}")

def put_discipline(name, day, pair, course):
    try:
        with connect_to_db() as conn:
            with conn.cursor() as cur:
                cur.execute('''
                    INSERT INTO disciplines (name_dis, dweek, nomp, nomk) 
                    VALUES (%s, %s, %s, %s)
                ''', (name, day, pair, course))
                conn.commit()
                print("Занятие успешно добавлено")
    except Error as e:
        print(f"Ошибка при добавлении занятия: {e}")

def delete_student(student_id):
    try:
        with connect_to_db() as conn:
            with conn.cursor() as cur:
                cur.execute('DELETE FROM students WHERE ids = %s', (student_id,))
                if cur.rowcount > 0:
                    conn.commit()
                    print("Студент успешно удален")
                else:
                    print("Студент не найден")
    except Error as e:
        print(f"Ошибка при удалении студента: {e}")

def delete_discipline(discipline_id):
    try:
        with connect_to_db() as conn:
            with conn.cursor() as cur:
                cur.execute('DELETE FROM disciplines WHERE id = %s', (discipline_id,))
                if cur.rowcount > 0:
                    conn.commit()
                    print("Занятие успешно удалено")
                else:
                    print("Занятие не найдено")
    except Error as e:
        print(f"Ошибка при удалении занятия: {e}")

def main():
    print('''
    Доступные команды:
    GET student [id] - получить информацию о студенте
    GET discipline [курс] - получить расписание для курса
    GET students [курс] - получить список студентов курса
    GET disciplines - получить полное расписание
    PUT student [имя] [курс] - добавить студента
    PUT discipline [название] [день] [пара] [курс] - добавить занятие
    DELETE student [id] - удалить студента
    DELETE discipline [id] - удалить занятие
    EXIT - выход
    ''')
    
    while True:
        try:
            command = input('Введите команду: ')
            if not command:
                continue
                
            # Разбиваем строку, сохраняя текст в кавычках как один элемент
            command = shlex.split(command)
                
            if command[0] == 'EXIT':
                break
                
            if len(command) < 2:
                print("Неверный формат команды")
                continue
                
            action, entity = command[0], command[1]
            
            if action == 'GET':
                if entity == 'student' and len(command) == 3:
                    get_student(int(command[2]))
                elif entity == 'discipline' and len(command) == 3:
                    get_discipline(int(command[2]))
                elif entity == 'students' and len(command) == 3:
                    get_students(int(command[2]))
                elif entity == 'disciplines' and len(command) == 2:
                    get_disciplines()
                else:
                    print("Неверный формат команды GET")
                    
            elif action == 'PUT':
                if entity == 'student' and len(command) == 4:
                    put_student(command[2], int(command[3]))
                elif entity == 'discipline' and len(command) == 6:
                    put_discipline(command[2], int(command[3]), int(command[4]), int(command[5]))
                else:
                    print("Неверный формат команды PUT")
                    
            elif action == 'DELETE':
                if entity == 'student' and len(command) == 3:
                    delete_student(int(command[2]))
                elif entity == 'discipline' and len(command) == 3:
                    delete_discipline(int(command[2]))
                else:
                    print("Неверный формат команды DELETE")
                    
            else:
                print("Неизвестная команда")
                
        except (ValueError, IndexError):
            print("Ошибка в формате команды")
        except Exception as e:
            print(f"Произошла ошибка: {e}")

if __name__ == "__main__":
    main() 