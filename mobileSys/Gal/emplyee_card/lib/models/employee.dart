/// מודל הנתונים של כרטיס העובד — תכנות מונחה-עצמים.
enum Sex { male, female, other }
 
enum MaritalStatus { single, married, divorced, widowed }
 
/// כתובת: עד 4 שורות + מיקוד.
class Address {
  final List<String> lines;
  final String postcode;
 
  Address({required List<String> lines, required String postcode})
      : lines = List.unmodifiable(
            lines.map((l) => l.trim()).where((l) => l.isNotEmpty)),
        postcode = postcode.trim().toUpperCase() {
    if (this.lines.isEmpty) throw ArgumentError('Address is required');
    if (this.lines.length > 4) throw ArgumentError('Max 4 address lines');
  }
 
  @override
  String toString() => [...lines, postcode].join(', ');
}
 
/// איש קשר לחירום — שורה בטבלה.
class EmergencyContact {
  final String name, relationship, workNumber, homeNumber, mobileNumber;
 
  EmergencyContact({
    required this.name,
    required this.relationship,
    this.workNumber = '',
    this.homeNumber = '',
    this.mobileNumber = '',
  }) {
    if (name.trim().isEmpty) throw ArgumentError('Contact name is required');
    if ([workNumber, homeNumber, mobileNumber].every((n) => n.trim().isEmpty)) {
      throw ArgumentError('At least one phone number is required');
    }
  }
}
 
/// פרטי תפקיד.
class JobDetails {
  final String supervisor, department, location, workType;
  const JobDetails({
    required this.supervisor,
    required this.department,
    required this.location,
    required this.workType,
  });
}
 
/// משך זמן בשנים / חודשים / ימים.
class Period {
  final int years, months, days;
  const Period(this.years, this.months, this.days);
 
  /// ההפרש בין שני תאריכים, בדיוק כמו «Length of service»:
  /// סופרים חודשים שלמים, ואת השארית — בימים.
  factory Period.between(DateTime from, DateTime to) {
    final f = DateTime.utc(from.year, from.month, from.day);
    final t = DateTime.utc(to.year, to.month, to.day);
    int months = (t.year - f.year) * 12 + t.month - f.month;
    var anchor = _addMonths(f, months);
    if (anchor.isAfter(t)) {
      months--;
      anchor = _addMonths(f, months);
    }
    return Period(months ~/ 12, months % 12, t.difference(anchor).inDays);
  }
 
  /// הוספת חודשים עם «הצמדה» לסוף החודש (31 בינואר + חודש = 28/29 בפברואר).
  static DateTime _addMonths(DateTime d, int months) {
    final y = d.year + (d.month - 1 + months) ~/ 12;
    final m = (d.month - 1 + months) % 12 + 1;
    final last = DateTime.utc(y, m + 1, 0).day;
    return DateTime.utc(y, m, d.day > last ? last : d.day);
  }
 
  @override
  String toString() => '$years Years $months Months $days Days';
}
 
/// אדם — מחלקת בסיס.
class Person {
  final String name;
  final String knownAs;
  final DateTime dateOfBirth;
  final bool dobVerified;
  final Sex sex;
  final MaritalStatus maritalStatus;
  final String maidenName;
  final String nationality;
  final String ethnicOrigin; // רגיש: אופציונלי, ברירת מחדל «לא צוין»
  final Address address;
  final String tel;
  final String mobile;
 
  Person({
    required this.name,
    this.knownAs = '',
    required this.dateOfBirth,
    this.dobVerified = false,
    required this.sex,
    required this.maritalStatus,
    this.maidenName = '',
    required this.nationality,
    this.ethnicOrigin = 'Prefer not to say',
    required this.address,
    this.tel = '',
    this.mobile = '',
  }) {
    if (name.trim().isEmpty) throw ArgumentError('Name is required');
    if (dateOfBirth.isAfter(DateTime.now())) {
      throw ArgumentError('Date of birth cannot be in the future');
    }
  }
 
  /// גיל בשנים שלמות ביום נתון.
  int ageOn(DateTime day) => Period.between(dateOfBirth, day).years;
  int get age => ageOn(DateTime.now());
 
  /// שם הפנייה: «Known As» אם קיים, אחרת השם המלא.
  String get displayName => knownAs.trim().isNotEmpty ? knownAs : name;
}
 
/// עובד — יורש מ-Person ומוסיף נתוני העסקה.
class Employee extends Person {
  final int employeeNumber;
  final String jobTitle;
  final int dependents;
  final bool director;
  final JobDetails job;
  final DateTime joinDate;
  final DateTime? leaveDate; // null = עדיין עובד בחברה
  final bool hasPhoto;
  final List<EmergencyContact> emergencyContacts;
 
  Employee({
    required this.employeeNumber,
    required this.jobTitle,
    required super.name,
    super.knownAs,
    required super.dateOfBirth,
    super.dobVerified,
    required super.sex,
    required super.maritalStatus,
    super.maidenName,
    required super.nationality,
    super.ethnicOrigin,
    required super.address,
    super.tel,
    super.mobile,
    this.dependents = 0,
    this.director = false,
    required this.job,
    required this.joinDate,
    this.leaveDate,
    this.hasPhoto = false,
    List<EmergencyContact> emergencyContacts = const [],
  }) : emergencyContacts = List.unmodifiable(emergencyContacts) {
    if (employeeNumber <= 0) throw ArgumentError('Employee number must be positive');
    if (dependents < 0 || dependents > 20) throw ArgumentError('Dependents must be 0-20');
    if (ageOn(joinDate) < 16) throw ArgumentError('Employee must be at least 16 at join date');
    if (leaveDate != null && leaveDate!.isBefore(joinDate)) {
      throw ArgumentError('Leave date cannot be before join date');
    }
  }
 
  bool get hasLeft => leaveDate != null;
 
  /// ותק: מתאריך ההצטרפות עד היום (או עד תאריך העזיבה).
  Period lengthOfServiceOn(DateTime day) =>
      Period.between(joinDate, leaveDate != null && leaveDate!.isBefore(day) ? leaveDate! : day);
  Period get lengthOfService => lengthOfServiceOn(DateTime.now());
 
  /// עותק עם שינויים — אובייקטים אימיוטביליים מתעדכנים כך.
  Employee copyWith({bool? hasPhoto, List<EmergencyContact>? emergencyContacts}) => Employee(
        employeeNumber: employeeNumber,
        jobTitle: jobTitle,
        name: name,
        knownAs: knownAs,
        dateOfBirth: dateOfBirth,
        dobVerified: dobVerified,
        sex: sex,
        maritalStatus: maritalStatus,
        maidenName: maidenName,
        nationality: nationality,
        ethnicOrigin: ethnicOrigin,
        address: address,
        tel: tel,
        mobile: mobile,
        dependents: dependents,
        director: director,
        job: job,
        joinDate: joinDate,
        leaveDate: leaveDate,
        hasPhoto: hasPhoto ?? this.hasPhoto,
        emergencyContacts: emergencyContacts ?? this.emergencyContacts,
      );
 
  @override
  String toString() => 'Employee #$employeeNumber $name ($jobTitle)';
}
 
/// כללי אימות לשדות הטופס — מחזירים הודעת שגיאה או null.
class Validators {
  static String? required(String? v, String field) =>
      (v == null || v.trim().isEmpty) ? '$field is required' : null;
 
  static String? phone(String? v, {bool optional = true}) {
    if (v == null || v.trim().isEmpty) return optional ? null : 'Phone is required';
    return RegExp(r'^\+?[0-9 ()\-]{7,16}$').hasMatch(v.trim()) ? null : 'Invalid phone number';
  }
 
  /// מיקוד בריטי, למשל HD1 3XY.
  static String? ukPostcode(String? v) {
    if (v == null || v.trim().isEmpty) return 'Postcode is required';
    return RegExp(r'^[A-Z]{1,2}[0-9][A-Z0-9]? ?[0-9][A-Z]{2}$', caseSensitive: false)
            .hasMatch(v.trim())
        ? null
        : 'Invalid UK postcode';
  }
 
  static String? intRange(String? v, String field, int min, int max) {
    final n = int.tryParse(v?.trim() ?? '');
    if (n == null) return '$field must be a whole number';
    return (n < min || n > max) ? '$field must be $min-$max' : null;
  }
}