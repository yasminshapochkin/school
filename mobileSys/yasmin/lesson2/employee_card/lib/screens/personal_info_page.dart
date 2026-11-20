import 'package:material_ui/material_ui.dart';
import '../models/person.dart';

class PersonalInfoPage extends StatefulWidget {
  const PersonalInfoPage({super.key});

  @override
  State<PersonalInfoPage> createState() => _PersonalInfoPageState();
}

class _PersonalInfoPageState extends State<PersonalInfoPage> {
  final _formKey = GlobalKey<FormState>();
  final _name = TextEditingController();
  final _address = TextEditingController();
  final _mobile = TextEditingController();
  final _rate = TextEditingController();
  final _birth = TextEditingController();
  final _hours = TextEditingController();
  DateTime? _birthDate;
  Employee? _employee; // התוצאה האחרונה

  @override
  void dispose() {
    for (final c in [_name, _address, _mobile, _rate, _birth, _hours]) {
      c.dispose();
    }
    super.dispose();
  }

  String _fmt(DateTime d) =>
      '${d.day.toString().padLeft(2, '0')}/${d.month.toString().padLeft(2, '0')}/${d.year}';

  Future<void> _pickDate() async {
    final picked = await showDatePicker(
      context: context,
      initialDate: _birthDate ?? DateTime(2000, 1, 17),
      firstDate: DateTime(1900),
      lastDate: DateTime.now(),
    );
    if (picked != null) {
      setState(() {
        _birthDate = picked;
        _birth.text = _fmt(picked);
      });
    }
  }

  void _calculate() {
    if (!_formKey.currentState!.validate()) return;
    setState(() {
      _employee = Employee(
        name: _name.text,
        address: _address.text,
        mobile: _mobile.text,
        birthDate: _birthDate!,
        hourlyRate: double.parse(_rate.text),
        hoursWorked: double.parse(_hours.text),
      );
    });
  }

  Widget _field(String label, TextEditingController c,
      {String? Function(String?)? validator,
      TextInputType? keyboard,
      bool readOnly = false,
      VoidCallback? onTap,
      Widget? suffix,
      Key? key}) {
    return Padding(
      padding: const EdgeInsets.only(bottom: 12),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(label, style: const TextStyle(fontWeight: FontWeight.bold)),
          const SizedBox(height: 6),
          TextFormField(
            key: key,
            controller: c,
            validator: validator,
            keyboardType: keyboard,
            readOnly: readOnly,
            onTap: onTap,
            decoration: InputDecoration(
              border: const OutlineInputBorder(),
              isDense: true,
              suffixIcon: suffix,
            ),
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: SingleChildScrollView(
          padding: const EdgeInsets.all(16),
          child: ConstrainedBox(
            constraints: const BoxConstraints(maxWidth: 480),
            child: Card(
              child: Padding(
                padding: const EdgeInsets.all(20),
                child: Form(
                  key: _formKey,
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: [
                      const Text('Personal Info & Salary Calculator',
                          textAlign: TextAlign.center,
                          style: TextStyle(fontSize: 26, fontWeight: FontWeight.bold)),
                      const SizedBox(height: 16),
                      _field('Name:', _name,
                          key: const Key('name'),
                          validator: (v) => Validators.required(v, 'Name')),
                      _field('Address:', _address,
                          key: const Key('address'),
                          validator: (v) => Validators.required(v, 'Address')),
                      _field('Mobile:', _mobile,
                          key: const Key('mobile'),
                          keyboard: TextInputType.phone,
                          validator: Validators.mobile),
                      _field('Hourly Rate:', _rate,
                          key: const Key('rate'),
                          keyboard: const TextInputType.numberWithOptions(decimal: true),
                          validator: (v) => Validators.positiveNumber(v, 'Hourly rate')),
                      _field('Birth Date:', _birth,
                          key: const Key('birth'),
                          readOnly: true,
                          onTap: _pickDate,
                          suffix: const Icon(Icons.calendar_today),
                          validator: (_) =>
                              _birthDate == null ? 'Birth date is required' : null),
                      _field('Hours Worked:', _hours,
                          key: const Key('hours'),
                          keyboard: TextInputType.number,
                          validator: Validators.hours),
                      FilledButton(
                        key: const Key('calc'),
                        style: FilledButton.styleFrom(
                          backgroundColor: const Color(0xFF007BFF),
                          shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(4)),
                          padding: const EdgeInsets.symmetric(vertical: 16),
                        ),
                        onPressed: _calculate,
                        child: const Text('Calculate'),
                      ),
                      if (_employee != null) ...[
                        const SizedBox(height: 16),
                        Card(
                          color: Colors.grey.shade100,
                          child: Padding(
                            padding: const EdgeInsets.all(16),
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: [
                                const Text('Results:',
                                    style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold)),
                                const SizedBox(height: 8),
                                Text('Age: ${_employee!.age} years', key: const Key('age')),
                                Text('Salary: \$${_employee!.salary.toStringAsFixed(2)}',
                                    key: const Key('salary')),
                              ],
                            ),
                          ),
                        ),
                      ],
                    ],
                  ),
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }
}
