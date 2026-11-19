import 'package:material_ui/material_ui.dart';
import 'screens/employee_card_page.dart';
import 'services/employee_repository.dart';
 
void main() => runApp(const EmployeeCardApp());
 
class EmployeeCardApp extends StatelessWidget {
  final DateTime Function() today;
  const EmployeeCardApp({super.key, this.today = DateTime.now});
 
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Employee Card',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(colorSchemeSeed: const Color(0xFF1F5FA8), useMaterial3: true),
      home: EmployeeCardPage(repository: EmployeeRepository.withSampleData(), today: today),
    );
  }
}