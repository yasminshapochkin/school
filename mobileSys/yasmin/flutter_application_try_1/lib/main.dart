import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'task_controller.dart';
import 'task_pages.dart';
import 'task_repository.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  runApp(const TaskApp());
}

class _TaskAppState extends State<TaskApp> {
  late final TaskController controller;

  @override
  void initState() {
    super.initState();
    controller = TaskController(
      PreferencesTaskRepository(SharedPreferencesAsync()),
    );
    controller.load();
  }

  @override
  void dispose() {
    controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) => MaterialApp(
    debugShowCheckedModeBanner: false,
    title: 'מנהל משימות',
    theme: ThemeData(colorSchemeSeed: Colors.indigo, useMaterial3: true),
    builder: (context, child) => Directionality(
      textDirection: TextDirection.rtl,
      child: child ?? const SizedBox.shrink(),
    ),
    home: TaskListPage(controller: controller),
  );
}