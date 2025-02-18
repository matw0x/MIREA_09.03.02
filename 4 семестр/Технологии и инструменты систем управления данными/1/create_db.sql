-- Создание базы данных
CREATE DATABASE study;

-- Подключение к базе данных
\c study;

-- Создание таблицы students
CREATE TABLE students (
    ids INTEGER PRIMARY KEY,
    name_st VARCHAR(100) NOT NULL,
    nomk INTEGER CHECK (nomk BETWEEN 1 AND 8) NOT NULL
);

-- Создание таблицы disciplines
CREATE TABLE disciplines (
    id SERIAL PRIMARY KEY,
    name_dis VARCHAR(100) NOT NULL,
    dweek INTEGER CHECK (dweek BETWEEN 1 AND 7) NOT NULL,
    nomp INTEGER CHECK (nomp BETWEEN 1 AND 8) NOT NULL,
    nomk INTEGER CHECK (nomk BETWEEN 1 AND 8) NOT NULL,
    UNIQUE (dweek, nomp, nomk)
);

-- Копирование данных из CSV-файла в таблицу students
COPY students(ids, name_st, nomk) 
FROM '/mnt/c/Users/boltf/OneDrive/Рабочий стол/nurmatova/1/students.csv'
DELIMITER ';' 
CSV;