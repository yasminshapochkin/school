/// מודל הנתונים של האפליקציה — תכנות מונחה-עצמים.
/// Person מחזיק פרטים אישיים; Employee יורש ממנו ומוסיף נתוני שכר.
class Person {
  final String _name;
  final String _address;
  final String _mobile;
  final DateTime _birthDate;
 
  Person({
    required String name,
    required String address,
    required String mobile,
    required DateTime birthDate,
  })  : _name = name.trim(),
        _address = address.trim(),
        _mobile = mobile.trim(),
        _birthDate = birthDate {
    if (_name.isEmpty) throw ArgumentError('Name is required');
    if (birthDate.isAfter(DateTime.now())) {
      throw ArgumentError('Birth date cannot be in the future');
    }
  }
 
  // Getters — קריאה בלבד מבחוץ (Encapsulation)
  String get name => _name;
  String get address => _address;
  String get mobile => _mobile;
  DateTime get birthDate => _birthDate;
 
  /// גיל בשנים שלמות ביום נתון (נוח לבדיקות).
  int ageOn(DateTime today) {
    int age = today.year - _birthDate.year;
    final hadBirthday = today.month > _birthDate.month ||
        (today.month == _birthDate.month && today.day >= _birthDate.day);
    if (!hadBirthday) age--;
    return age;
  }
 
  int get age => ageOn(DateTime.now());
 
  @override
  String toString() => 'Person($_name, $_address, $_mobile)';
}
 
class Employee extends Person {
  final double _hourlyRate;
  final double _hoursWorked;
 
  Employee({
    required super.name,
    required super.address,
    required super.mobile,
    required super.birthDate,
    required double hourlyRate,
    required double hoursWorked,
  })  : _hourlyRate = hourlyRate,
        _hoursWorked = hoursWorked {
    if (hourlyRate <= 0) throw ArgumentError('Hourly rate must be positive');
    if (hoursWorked < 0) throw ArgumentError('Hours cannot be negative');
  }
 
  double get hourlyRate => _hourlyRate;
  double get hoursWorked => _hoursWorked;
 
  /// שכר = שעות × תעריף לשעה
  double get salary => _hourlyRate * _hoursWorked;
 
  @override
  String toString() =>
      'Employee($name, age $age, salary \$${salary.toStringAsFixed(2)})';
}
 
/// פונקציות אימות לשדות הטופס — מחזירות הודעת שגיאה או null.
class Validators {
  static String? required(String? v, String field) =>
      (v == null || v.trim().isEmpty) ? '$field is required' : null;
 
  static String? mobile(String? v) {
    if (v == null || v.trim().isEmpty) return 'Mobile is required';
    final ok = RegExp(r'^\+?[0-9 \-]{7,15}$').hasMatch(v.trim());
    return ok ? null : 'Enter a valid phone number';
  }
 
  static String? positiveNumber(String? v, String field) {
    final n = double.tryParse(v?.trim() ?? '');
    if (n == null) return '$field must be a number';
    if (n <= 0) return '$field must be greater than 0';
    return null;
  }
 
  static String? hours(String? v) {
    final n = double.tryParse(v?.trim() ?? '');
    if (n == null) return 'Hours must be a number';
    if (n < 0 || n > 744) return 'Hours must be between 0 and 744';
    return null;
  }
}