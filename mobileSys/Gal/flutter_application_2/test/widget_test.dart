import 'package:flutter_test/flutter_test.dart';
import 'package:personal_info/models/person.dart';
 
void main() {
  Employee john({double rate = 35, double hours = 182}) => Employee(
        name: 'John Duo',
        address: 'New York',
        mobile: '+1 5566222446',
        birthDate: DateTime(2000, 1, 17),
        hourlyRate: rate,
        hoursWorked: hours,
      );
 
  test('salary = rate x hours', () {
    expect(john().salary, 6370.0);              // 35 × 182
    expect(john(rate: 40).salary, 7280.0);      // 40 × 182
  });
 
  test('age counts only completed birthdays', () {
    final e = john();
    expect(e.ageOn(DateTime(2024, 6, 1)), 24);
    expect(e.ageOn(DateTime(2026, 1, 16)), 25); // day before birthday
    expect(e.ageOn(DateTime(2026, 1, 17)), 26); // birthday
  });
 
  test('Employee is a Person (inheritance)', () {
    expect(john(), isA<Person>());
  });
 
  test('invalid values throw', () {
    expect(() => john(rate: 0), throwsArgumentError);
    expect(() => john(hours: -1), throwsArgumentError);
  });
 
  test('validators', () {
    expect(Validators.mobile('+1 5566222446'), isNull);
    expect(Validators.mobile('abc'), isNotNull);
    expect(Validators.positiveNumber('0', 'Rate'), isNotNull);
    expect(Validators.hours('800'), isNotNull);
  });
}