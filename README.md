# Vladov_Library

Това хранилище съдържа C++ имплементация на малка библиотечна система. Проектът демонстрира основни и напреднали концепции на обектно-ориентираното програмиране, включително капсулация, асоциация между обекти, управление на паметта (Rule of 5) и работа със стандартната библиотека (STL).

---

## Структура на проекта
- **LibrarySystem.h**: Дефиниции на класовете и техните интерфейси.
- **LibrarySystem.cpp**: Имплементация на методите, статичните членове и бизнес логиката.
- **main.cpp**: Демонстрационен файл, който тества функционалността и показва жизнения цикъл на обектите.

---

## Описание на Класовете

### 1. Author
Представя автор на книга. Този клас е проектиран като прост контейнер на данни (Data Class) с валидация.

**Членове:** име и година на раждане.

**Валидация:** При задаване на година на раждане се проверява дали е в диапазона `[1850 - 2025]`. Ако е извън него, се задава стойност по подразбиране (`1900`).

**Интерфейс:** Използва `const` методи за достъп до данните.

---

### 2. Book (Демонстрация на Rule of 5)
Централният клас в системата. Той управлява информацията за конкретна книга и следи общия брой на живите инстанции.

**Статичен член:** `static int totalBooks` – увеличава се при създаване на обект и намалява при унищожаване.

**Rule of 5 — имплементирани методи:**
- Деструктор
- Copy Constructor
- Move Constructor
- Copy Assignment Operator
- Move Assignment Operator

**Инварианти:** цената не може да бъде отрицателна; годината трябва да е валидна.

---

### 3. Member
Представя читател в библиотеката.

**Идентификация:** всеки читател има уникален `memberId`.

**Логика:** при конструиране се проверява дали ID-то не е празен низ.

---

### 4. Loan
Асоциативен клас, който свързва **Book** и **Member**.

**Отговорност:** пази историята на заемането — кой (Member ID) е взел коя книга (ISBN), кога (Start Date) и докога (Due Date).

**Бизнес логика:**
- `isOverdue(today)`: Проверява дали книгата е просрочена чрез лексикографско сравнение на дати във формат `YYYY-MM-DD`.
- Конструкторът автоматично разменя датите, ако `startDate` е след `dueDate`.

---

### 5. Library
Мениджърски клас (**Facade pattern**), който управлява колекциите.

**Хранилище:** използва `std::vector` за съхранение на книги, членове и заеми.

**Ключови методи:**
- `loanBook(...)`: проверява дали книгата съществува, дали е налична и дали членът е валиден.
- `isBookAvailable(...)`: проверява за активни и невърнати заеми.
- `findByAuthor(...)`: връща списък от книги с автор, съдържащ подадения низ.

---

## Компилация и Стартиране
Проектът не използва външни библиотеки и може да бъде компилиран с всеки съвременен C++ компилатор.

**Изисквания:**
- Standard: `C++11` или по-нов (препоръчително `C++17`).

---

## Инструкции за терминал (GCC / Linux / macOS)
```bash
# 1. Компилиране на всички файлове
g++ -std=c++17 -Wall -Wextra -O2 -o library main.cpp LibrarySystem.cpp

# 2. Стартиране
./library
```

---

## Инструкции за Windows (MinGW / CMD)
```cmd
g++ -std=c++17 -Wall -Wextra -o library.exe main.cpp LibrarySystem.cpp
library.exe
```


---

## Примерен изход (Example Output)
```
--- Initializing Library ---
Current live books: 0
Current live books (after adding to vector): 6

=== Library Status ===
Total Books in Collection: 3
Total Members: 2
Total Loans (History): 0
Active Loans: 0
Global Book Instances (Static): 6
======================

--- Testing Loans ---
Success: 'Pod igoto' loaned to Petar.
Loan Failed: Book ISBN-001 is not available or does not exist.
Expected Fail: 'Pod igoto' is already loaned.
Is ISBN-001 available? false

--- Testing Returns ---
Returned ISBN-001.
Is ISBN-001 available? true

--- Search for 'Vazov' ---
'Pod igoto' by Ivan Vazov, 1894, $25.50 [ISBN: ISBN-001]
'Nema zemya' by Ivan Vazov, 1900, $18.90 [ISBN: ISBN-002]

--- Rule of 5 Scope Test ---
Inside scope live books: 9
Outside scope live books: 8
```
