import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Concatenation App',
      home: const CalcPage(),
    );
  }
}

class CalcPage extends StatefulWidget {
  const CalcPage({super.key});

  @override
  State<CalcPage> createState() => _CalcPageState();
}

class _CalcPageState extends State<CalcPage> {
  // Controllers for reading text fields
  final TextEditingController value1Controller = TextEditingController();
  final TextEditingController value2Controller = TextEditingController();

  // Result variable
  String result = '';

  // Function for concatenating two values
  void calculate() {
    String value1 = value1Controller.text;
    String value2 = value2Controller.text;
    setState(() {
      result = value1 + value2;
    });
  }



  @override
  void dispose() {
    value1Controller.dispose();
    value2Controller.dispose();
    super.dispose();
  }

  void clear() {
    setState(() {
      value1Controller.clear();
      value2Controller.clear();
      result = '';
    });
  }

  void add() {
    setState(() {
      double? num1 = double.tryParse(value1Controller.text);
      double? num2 = double.tryParse(value2Controller.text);

      if (num1 == null || num2 == null) {
        result = 'Invalid input';
      } else {
        result = (num1 + num2).toString();
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Flutter Calc Example'),
        backgroundColor: Colors.blue,
      ),
      body: Padding(
        padding: const EdgeInsets.all(20),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // First TextField
            TextField(
              controller: value1Controller,
              decoration: const InputDecoration(
                labelText: 'Enter First Value',
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 20),

            // Second TextField
            TextField(
              controller: value2Controller,
              decoration: const InputDecoration(
                labelText: 'Enter Second Value',
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 20),

            // Calc Button
            
            ElevatedButton(
              onPressed: calculate,
              child: const Text('concat'),
            ),
            
ElevatedButton(
  onPressed: clear,
  child: const Text('Clear'),
),
ElevatedButton(
  onPressed: add,
  child: const Text('Add'),
),
            const SizedBox(height: 30),

            // Result
            Text(
              'Result: $result',
              style: const TextStyle(
                fontSize: 24,
                fontWeight: FontWeight.bold,
              ),
            ),
          ],
        ),
      ),
    );
  }
}