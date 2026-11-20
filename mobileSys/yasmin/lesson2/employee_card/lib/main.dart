import 'package:material_ui/material_ui.dart';
import 'screens/personal_info_page.dart';

void main() => runApp(const PersonalInfoApp());

class PersonalInfoApp extends StatelessWidget {
  const PersonalInfoApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Personal Info',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(colorSchemeSeed: const Color(0xFF007BFF), useMaterial3: true),
      home: const PersonalInfoPage(),
    );
  }
}
