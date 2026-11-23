import 'package:flutter_test/flutter_test.dart';
import 'package:employee_card/models/employee.dart';
import 'package:employee_card/services/employee_repository.dart';
 
void main() {
  final simon = EmployeeRepository.withSampleData().byNumber(1)!;
 
  test('age matches the screenshot date (1 Dec 2005) and today', () {
    expect(simon.ageOn(DateTime(2005, 12, 1)), 26);
    expect(simon.ageOn(DateTime(2026, 11, 13)), 47);
  });
 
  test('length of service: 11 Nov 2004 → 1 Dec 2005 = 1y 0m 20d', () {
    expect(simon.lengthOfServiceOn(DateTime(2005, 12, 1)).toString(), '1 Years 0 Months 20 Days');
    expect(simon.lengthOfServiceOn(DateTime(2026, 11, 13)).toString(), '22 Years 0 Months 2 Days');
  });
 
  test('Period borrows days from the previous month', () {
    expect(Period.between(DateTime(2024, 1, 31), DateTime(2024, 3, 1)).toString(), '0 Years 1 Months 1 Days');
  });
 
  test('Employee is a Person; inheritance + displayName', () {
    expect(simon, isA<Person>());
    expect(simon.displayName, 'Simon Phillips');
  });
 
  test('constructor rejects invalid objects', () {
    Employee make({int number = 3, DateTime? join, DateTime? leave, int dependents = 0}) => Employee(
          employeeNumber: number,
          jobTitle: 'X',
          name: 'Test',
          dateOfBirth: DateTime(2000, 1, 1),
          sex: Sex.female,
          maritalStatus: MaritalStatus.single,
          nationality: 'Israeli',
          address: Address(lines: ['1 Main St'], postcode: 'HD1 3XY'),
          job: const JobDetails(supervisor: 'A', department: 'B', location: 'C', workType: 'D'),
          joinDate: join ?? DateTime(2020, 1, 1),
          leaveDate: leave,
          dependents: dependents,
        );
    expect(() => make(number: 0), throwsArgumentError);
    expect(() => make(join: DateTime(2010, 1, 1)), throwsArgumentError); // age 10 at join
    expect(() => make(leave: DateTime(2019, 1, 1)), throwsArgumentError);
    expect(() => make(dependents: 21), throwsArgumentError);
    expect(make(leave: DateTime(2022, 6, 30)).hasLeft, isTrue);
  });
 
  test('emergency contact needs a phone', () {
    expect(() => EmergencyContact(name: 'A', relationship: 'B'), throwsArgumentError);
  });
 
  test('validators', () {
    expect(Validators.ukPostcode('HD1 3XY'), isNull);
    expect(Validators.ukPostcode('12345'), isNotNull);
    expect(Validators.phone('0141 888 8888'), isNull);
    expect(Validators.intRange('21', 'Dependents', 0, 20), isNotNull);
  });
 
  test('repository: save, nextNumber, sort', () {
    final r = EmployeeRepository.withSampleData();
    expect(r.nextNumber, 3);
    expect(r.all.map((e) => e.employeeNumber), [1, 2]);
  });
}