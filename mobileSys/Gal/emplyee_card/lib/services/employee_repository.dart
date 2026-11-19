import '../models/employee.dart';
 
/// «מאגר» העובדים בזיכרון — מקביל ל-All Employees / Add / Edit / Save changes.
class EmployeeRepository {
  final Map<int, Employee> _items = {};
 
  List<Employee> get all =>
      _items.values.toList()..sort((a, b) => a.employeeNumber.compareTo(b.employeeNumber));
 
  Employee? byNumber(int n) => _items[n];
 
  int get nextNumber => _items.isEmpty ? 1 : _items.keys.reduce((a, b) => a > b ? a : b) + 1;
 
  /// שמירה: עובד חדש או עדכון של קיים.
  void save(Employee e) => _items[e.employeeNumber] = e;
 
  bool delete(int n) => _items.remove(n) != null;
 
  static EmployeeRepository withSampleData() {
    final repo = EmployeeRepository();
    repo.save(Employee(
      employeeNumber: 1,
      jobTitle: 'Electrician',
      name: 'Simon Phillips',
      dateOfBirth: DateTime(1979, 4, 1),
      sex: Sex.male,
      maritalStatus: MaritalStatus.single,
      nationality: 'British',
      address: Address(lines: ['12 Huddersfield Road', 'Huddersfield'], postcode: 'HD1 3XY'),
      tel: '0141 888 8888',
      mobile: '07815 888888',
      job: const JobDetails(
          supervisor: 'Alan Other', department: 'Production', location: 'Rochdale', workType: 'Electrical'),
      joinDate: DateTime(2004, 11, 11),
      hasPhoto: true,
    ));
    repo.save(Employee(
      employeeNumber: 2,
      jobTitle: 'Supervisor',
      name: 'Alan Other',
      dateOfBirth: DateTime(1970, 9, 23),
      dobVerified: true,
      sex: Sex.male,
      maritalStatus: MaritalStatus.married,
      dependents: 2,
      nationality: 'British',
      address: Address(lines: ['4 Mill Lane', 'Rochdale'], postcode: 'OL11 1AA'),
      mobile: '07700 900123',
      job: const JobDetails(
          supervisor: 'Jane Wilson', department: 'Production', location: 'Rochdale', workType: 'Management'),
      joinDate: DateTime(1998, 3, 2),
      emergencyContacts: [
        EmergencyContact(name: 'Mary Other', relationship: 'Wife', mobileNumber: '07700 900456'),
      ],
    ));
    return repo;
  }
}
 
