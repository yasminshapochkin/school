import 'package:material_ui/material_ui.dart';
import '../models/employee.dart';
import '../services/employee_repository.dart';
 
const departments = ['Production', 'Sales', 'Accounts', 'Warehouse', 'Management'];
const supervisors = ['Alan Other', 'Jane Wilson', 'Tom Baker'];
const ethnicOrigins = ['Prefer not to say', 'White British', 'White Other', 'Asian', 'Black', 'Mixed', 'Other'];
 
String fmtDate(DateTime d) {
  const m = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August',
    'September', 'October', 'November', 'December'];
  return '${d.day.toString().padLeft(2, '0')} ${m[d.month - 1]} ${d.year}';
}
 
class EmployeeCardPage extends StatefulWidget {
  final EmployeeRepository repository;
  final DateTime Function() today; // ניתן להחלפה בבדיקות
  const EmployeeCardPage({super.key, required this.repository, this.today = DateTime.now});
 
  @override
  State<EmployeeCardPage> createState() => _EmployeeCardPageState();
}
 
class _EmployeeCardPageState extends State<EmployeeCardPage> {
  final _formKey = GlobalKey<FormState>();
  final c = <String, TextEditingController>{
    for (final k in ['name', 'number', 'title', 'a1', 'a2', 'a3', 'a4', 'postcode', 'tel',
      'knownAs', 'mobile', 'dependents', 'maiden', 'nationality', 'location', 'workType'])
      k: TextEditingController()
  };
  DateTime? _dob, _joinDate, _leaveDate;
  bool _dobVerified = false, _director = false, _hasLeft = false, _hasPhoto = false;
  Sex _sex = Sex.male;
  MaritalStatus _marital = MaritalStatus.single;
  String _ethnic = ethnicOrigins.first, _supervisor = supervisors.first, _department = departments.first;
  List<EmergencyContact> _contacts = [];
  String _status = 'Ready';
 
  @override
  void initState() {
    super.initState();
    _load(widget.repository.all.first);
  }
 
  @override
  void dispose() {
    for (final x in c.values) {
      x.dispose();
    }
    super.dispose();
  }
 
  /// טעינת אובייקט Employee לתוך שדות הטופס.
  void _load(Employee e) {
    c['name']!.text = e.name;
    c['number']!.text = '${e.employeeNumber}';
    c['title']!.text = e.jobTitle;
    for (var i = 0; i < 4; i++) {
      c['a${i + 1}']!.text = i < e.address.lines.length ? e.address.lines[i] : '';
    }
    c['postcode']!.text = e.address.postcode;
    c['tel']!.text = e.tel;
    c['knownAs']!.text = e.knownAs;
    c['mobile']!.text = e.mobile;
    c['dependents']!.text = '${e.dependents}';
    c['maiden']!.text = e.maidenName;
    c['nationality']!.text = e.nationality;
    c['location']!.text = e.job.location;
    c['workType']!.text = e.job.workType;
    _dob = e.dateOfBirth;
    _joinDate = e.joinDate;
    _leaveDate = e.leaveDate;
    _hasLeft = e.hasLeft;
    _dobVerified = e.dobVerified;
    _director = e.director;
    _hasPhoto = e.hasPhoto;
    _sex = e.sex;
    _marital = e.maritalStatus;
    _ethnic = e.ethnicOrigin;
    _supervisor = e.job.supervisor;
    _department = e.job.department;
    _contacts = [...e.emergencyContacts];
  }
 
  void _newEmployee() {
    setState(() {
      for (final x in c.values) {
        x.clear();
      }
      c['number']!.text = '${widget.repository.nextNumber}';
      c['dependents']!.text = '0';
      _dob = null;
      _joinDate = widget.today();
      _leaveDate = null;
      _hasLeft = _dobVerified = _director = _hasPhoto = false;
      _sex = Sex.male;
      _marital = MaritalStatus.single;
      _ethnic = ethnicOrigins.first;
      _contacts = [];
      _status = 'New employee — fill in the card and choose “Save changes”';
    });
  }
 
  bool get _maidenEnabled => _sex == Sex.female && _marital != MaritalStatus.single;
 
  /// בניית אובייקט Employee מהטופס ושמירה במאגר.
  void _save() {
    if (!_formKey.currentState!.validate()) {
      setState(() => _status = 'Please correct the highlighted fields');
      return;
    }
    try {
      final e = Employee(
        employeeNumber: int.parse(c['number']!.text),
        jobTitle: c['title']!.text.trim(),
        name: c['name']!.text.trim(),
        knownAs: c['knownAs']!.text,
        dateOfBirth: _dob!,
        dobVerified: _dobVerified,
        sex: _sex,
        maritalStatus: _marital,
        maidenName: _maidenEnabled ? c['maiden']!.text.trim() : '',
        nationality: c['nationality']!.text.trim(),
        ethnicOrigin: _ethnic,
        address: Address(
            lines: [c['a1']!.text, c['a2']!.text, c['a3']!.text, c['a4']!.text],
            postcode: c['postcode']!.text),
        tel: c['tel']!.text.trim(),
        mobile: c['mobile']!.text.trim(),
        dependents: int.parse(c['dependents']!.text),
        director: _director,
        job: JobDetails(
            supervisor: _supervisor,
            department: _department,
            location: c['location']!.text.trim(),
            workType: c['workType']!.text.trim()),
        joinDate: _joinDate!,
        leaveDate: _hasLeft ? _leaveDate : null,
        hasPhoto: _hasPhoto,
        emergencyContacts: _contacts,
      );
      widget.repository.save(e);
      setState(() => _status = 'Saved: $e');
    } on ArgumentError catch (err) {
      setState(() => _status = 'Error: ${err.message}');
    }
  }
 
  Future<void> _pickDate(DateTime? current, ValueChanged<DateTime> onPicked) async {
    final d = await showDatePicker(
      context: context,
      initialDate: current ?? DateTime(1990, 1, 1),
      firstDate: DateTime(1900),
      lastDate: widget.today(),
    );
    if (d != null) setState(() => onPicked(d));
  }
 
  Future<void> _addContact() async {
    final contact = await showDialog<EmergencyContact>(context: context, builder: (_) => const ContactDialog());
    if (contact != null) setState(() => _contacts = [..._contacts, contact]);
  }
 
  // ---------- small UI helpers ----------
  Widget _text(String label, String k,
      {String? Function(String?)? validator, bool enabled = true, double width = 220, TextInputType? kb}) {
    return SizedBox(
      width: width,
      child: TextFormField(
        key: Key(k),
        controller: c[k],
        enabled: enabled,
        keyboardType: kb,
        validator: enabled ? validator : null,
        decoration: InputDecoration(labelText: label, isDense: true, border: const OutlineInputBorder()),
      ),
    );
  }
 
  Widget _group(String title, List<Widget> children, {double width = 340}) => SizedBox(
        width: width,
        child: Card(
          child: Padding(
            padding: const EdgeInsets.all(12),
            child: Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
              Text(title, style: const TextStyle(color: Color(0xFF1F5FA8), fontWeight: FontWeight.w600)),
              const SizedBox(height: 10),
              Wrap(spacing: 10, runSpacing: 10, children: children),
            ]),
          ),
        ),
      );
 
  Widget _dropdown<T>(String label, T value, List<T> items, String Function(T) text,
      ValueChanged<T> onChanged, {String? key}) {
    return SizedBox(
      width: 220,
      child: DropdownButtonFormField<T>(
        key: key == null ? null : Key(key),
        initialValue: value,
        isDense: true,
        isExpanded: true,
        decoration: InputDecoration(labelText: label, border: const OutlineInputBorder(), isDense: true),
        items: [for (final i in items) DropdownMenuItem(value: i, child: Text(text(i)))],
        onChanged: (v) => setState(() => onChanged(v as T)),
      ),
    );
  }
 
  Widget _dateField(String label, DateTime? value, ValueChanged<DateTime> onPicked,
      {bool enabled = true, String? key, bool required = true}) {
    return SizedBox(
      width: 220,
      child: FormField<DateTime>(
        validator: (_) => enabled && required && value == null ? '$label is required' : null,
        builder: (state) => InkWell(
          key: key == null ? null : Key(key),
          onTap: enabled ? () => _pickDate(value, onPicked) : null,
          child: InputDecorator(
            isEmpty: value == null,
            decoration: InputDecoration(
              labelText: label,
              enabled: enabled,
              isDense: true,
              border: const OutlineInputBorder(),
              suffixIcon: const Icon(Icons.calendar_month),
              errorText: state.errorText,
            ),
            child: Text(value == null ? '' : fmtDate(value)),
          ),
        ),
      ),
    );
  }
 
  Widget _sideMenu() {
    const sections = {
      'Employee': ['All Employees', 'Add Employee', 'Edit Employee', 'Save changes'],
      'Training & Disciplinary': ['Appraisals', 'Training History', 'Skills'],
      'Employment Details': ['Salary History', 'Absences', 'Job History'],
      'Logged On User': ['Administration', 'Tasks'],
    };
    return SizedBox(
      width: 210,
      child: ListView(children: [
        for (final s in sections.entries) ...[
          ListTile(title: Text(s.key, style: const TextStyle(fontWeight: FontWeight.bold)), dense: true),
          for (final item in s.value)
            ListTile(
              key: Key('menu-$item'),
              dense: true,
              contentPadding: const EdgeInsets.only(left: 28),
              title: Text(item),
              onTap: () => _menu(item),
            ),
        ],
      ]),
    );
  }
 
  void _menu(String item) {
    switch (item) {
      case 'All Employees':
        _showAll();
      case 'Add Employee':
        _newEmployee();
      case 'Save changes':
        _save();
      case 'Edit Employee':
        setState(() => _status = 'Editing employee #${c['number']!.text}');
      default:
        setState(() => _status = '“$item” is not part of this lab');
    }
  }
 
  void _showAll() {
    showDialog<void>(
      context: context,
      builder: (ctx) => SimpleDialog(
        title: const Text('All Employees'),
        children: [
          for (final e in widget.repository.all)
            SimpleDialogOption(
              key: Key('emp-${e.employeeNumber}'),
              onPressed: () {
                Navigator.pop(ctx);
                setState(() {
                  _load(e);
                  _status = 'Loaded $e';
                });
              },
              child: Text('#${e.employeeNumber}  ${e.name} — ${e.jobTitle}'),
            ),
        ],
      ),
    );
  }
 
  @override
  Widget build(BuildContext context) {
    final today = widget.today();
    final age = _dob == null ? '' : '${Period.between(_dob!, today).years}';
    final service = _joinDate == null
        ? ''
        : Period.between(_joinDate!, _hasLeft && _leaveDate != null && _leaveDate!.isBefore(today) ? _leaveDate! : today)
            .toString();
    return Scaffold(
      appBar: AppBar(title: const Text('HR Manager – Employee Card'), backgroundColor: const Color(0xFFDDE7F3)),
      body: Row(children: [
        _sideMenu(),
        const VerticalDivider(width: 1),
        Expanded(
          child: Form(
            key: _formKey,
            child: SingleChildScrollView(
              padding: const EdgeInsets.all(12),
              child: Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
                Card(
                  child: Padding(
                    padding: const EdgeInsets.all(12),
                    child: Wrap(spacing: 10, runSpacing: 10, children: [
                      _text('Employee Name', 'name', width: 260, validator: (v) => Validators.required(v, 'Name')),
                      _text('Employee Number', 'number', width: 150, kb: TextInputType.number,
                          validator: (v) => Validators.intRange(v, 'Number', 1, 99999)),
                      _text('Job Title', 'title', validator: (v) => Validators.required(v, 'Job title')),
                    ]),
                  ),
                ),
                Wrap(spacing: 8, runSpacing: 8, children: [
                  _group('Address & Contact', [
                    _text('Address line 1', 'a1', validator: (v) => Validators.required(v, 'Address')),
                    _text('Address line 2', 'a2'),
                    _text('Address line 3', 'a3'),
                    _text('Address line 4', 'a4'),
                    _text('Postcode', 'postcode', validator: Validators.ukPostcode),
                    _text('Tel', 'tel', kb: TextInputType.phone, validator: Validators.phone),
                    _text('Known As', 'knownAs'),
                    _text('Mobile', 'mobile', kb: TextInputType.phone, validator: Validators.phone),
                  ]),
                  _group('Personal', [
                    _dropdown('Sex', _sex, Sex.values, (s) => s.name, (v) => _sex = v, key: 'sex'),
                    _dropdown('Marital Status', _marital, MaritalStatus.values, (s) => s.name,
                        (v) => _marital = v, key: 'marital'),
                    Row(mainAxisSize: MainAxisSize.min, children: [
                      _text('Dependents', 'dependents', width: 120, kb: TextInputType.number,
                          validator: (v) => Validators.intRange(v, 'Dependents', 0, 20)),
                      IconButton(
                          key: const Key('dep-minus'),
                          icon: const Icon(Icons.remove),
                          onPressed: () => setState(() {
                                final n = int.tryParse(c['dependents']!.text) ?? 0;
                                if (n > 0) c['dependents']!.text = '${n - 1}';
                              })),
                      IconButton(
                          key: const Key('dep-plus'),
                          icon: const Icon(Icons.add),
                          onPressed: () => setState(() {
                                final n = int.tryParse(c['dependents']!.text) ?? 0;
                                if (n < 20) c['dependents']!.text = '${n + 1}';
                              })),
                    ]),
                    _text('Maiden Name', 'maiden', enabled: _maidenEnabled),
                    _dropdown('Ethnic Origin (optional)', _ethnic, ethnicOrigins, (s) => s, (v) => _ethnic = v),
                    _text('Nationality', 'nationality', validator: (v) => Validators.required(v, 'Nationality')),
                    SizedBox(
                      width: 220,
                      child: CheckboxListTile(
                        key: const Key('director'),
                        dense: true,
                        title: const Text('Director'),
                        value: _director,
                        onChanged: (v) => setState(() => _director = v!),
                      ),
                    ),
                  ]),
                  _group('Date of Birth', [
                    _dateField('Date of Birth', _dob, (d) => _dob = d, key: 'dob'),
                    SizedBox(width: 220, child: Text('Age: $age', key: const Key('age'))),
                    SizedBox(
                      width: 220,
                      child: CheckboxListTile(
                        dense: true,
                        title: const Text('DOB Verified'),
                        value: _dobVerified,
                        onChanged: (v) => setState(() => _dobVerified = v!),
                      ),
                    ),
                  ], width: 260),
                  _group('Job Details', [
                    _dropdown('Supervisor', _supervisor, supervisors, (s) => s, (v) => _supervisor = v),
                    _dropdown('Department', _department, departments, (s) => s, (v) => _department = v),
                    _text('Location', 'location', validator: (v) => Validators.required(v, 'Location')),
                    _text('Work Type', 'workType'),
                  ], width: 260),
                  _group('Employee Photograph', [
                    CircleAvatar(
                      key: const Key('photo'),
                      radius: 48,
                      backgroundColor: _hasPhoto ? const Color(0xFF1F5FA8) : const Color(0xFFE0E0E0),
                      child: _hasPhoto
                          ? Text(c['name']!.text.split(' ').where((w) => w.isNotEmpty).map((w) => w[0]).take(2).join(),
                              style: const TextStyle(fontSize: 32, color: Color(0xFFFFFFFF)))
                          : const Icon(Icons.person, size: 48),
                    ),
                    Column(mainAxisSize: MainAxisSize.min, children: [
                      OutlinedButton(
                          key: const Key('add-pic'),
                          onPressed: _hasPhoto ? null : () => setState(() => _hasPhoto = true),
                          child: const Text('Add Picture')),
                      OutlinedButton(
                          key: const Key('del-pic'),
                          onPressed: _hasPhoto ? () => setState(() => _hasPhoto = false) : null,
                          child: const Text('Delete Picture')),
                    ]),
                  ], width: 260),
                  _group('Employment Dates', [
                    SizedBox(width: 220, child: Text('Length of service\n$service', key: const Key('service'))),
                    _dateField('Join Date', _joinDate, (d) => _joinDate = d, key: 'join'),
                    SizedBox(
                      width: 220,
                      child: CheckboxListTile(
                        key: const Key('has-left'),
                        dense: true,
                        title: Text('Has the employee left the company?  ${_hasLeft ? 'Yes' : 'No'}'),
                        value: _hasLeft,
                        onChanged: (v) => setState(() => _hasLeft = v!),
                      ),
                    ),
                    _dateField('Leave Date', _leaveDate, (d) => _leaveDate = d, enabled: _hasLeft, key: 'leave'),
                  ], width: 260),
                ]),
                Card(
                  child: Padding(
                    padding: const EdgeInsets.all(12),
                    child: Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
                      Row(children: [
                        const Text('Emergency Contacts',
                            style: TextStyle(color: Color(0xFF1F5FA8), fontWeight: FontWeight.w600)),
                        const Spacer(),
                        TextButton.icon(
                            key: const Key('add-contact'),
                            onPressed: _addContact,
                            icon: const Icon(Icons.add),
                            label: const Text('Add contact')),
                      ]),
                      SingleChildScrollView(
                        scrollDirection: Axis.horizontal,
                        child: DataTable(
                          columns: const [
                            DataColumn(label: Text('Name')),
                            DataColumn(label: Text('Relationship')),
                            DataColumn(label: Text('Work Number')),
                            DataColumn(label: Text('Home Number')),
                            DataColumn(label: Text('Mobile Number')),
                            DataColumn(label: Text('')),
                          ],
                          rows: [
                            for (final (i, ec) in _contacts.indexed)
                              DataRow(cells: [
                                DataCell(Text(ec.name)),
                                DataCell(Text(ec.relationship)),
                                DataCell(Text(ec.workNumber)),
                                DataCell(Text(ec.homeNumber)),
                                DataCell(Text(ec.mobileNumber)),
                                DataCell(IconButton(
                                    icon: const Icon(Icons.delete_outline),
                                    onPressed: () => setState(() => _contacts = [..._contacts]..removeAt(i)))),
                              ]),
                          ],
                        ),
                      ),
                    ]),
                  ),
                ),
                const SizedBox(height: 8),
                Row(children: [
                  FilledButton.icon(
                      key: const Key('save'),
                      onPressed: _save,
                      icon: const Icon(Icons.save),
                      label: const Text('Save changes')),
                ]),
              ]),
            ),
          ),
        ),
      ]),
      bottomNavigationBar: Container(
        color: const Color(0xFFECECEC),
        padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 6),
        child: Text(_status, key: const Key('status')),
      ),
    );
  }
}
 
/// דיאלוג נפרד שמחזיק את ה-controllers שלו ומחזיר אובייקט EmergencyContact.
class ContactDialog extends StatefulWidget {
  const ContactDialog({super.key});
 
  @override
  State<ContactDialog> createState() => _ContactDialogState();
}
 
class _ContactDialogState extends State<ContactDialog> {
  final _key = GlobalKey<FormState>();
  final _f = {for (final k in ['name', 'rel', 'work', 'home', 'mobile']) k: TextEditingController()};
  String? _error;
 
  @override
  void dispose() {
    for (final x in _f.values) {
      x.dispose();
    }
    super.dispose();
  }
 
  void _ok() {
    if (!_key.currentState!.validate()) return;
    try {
      Navigator.pop(
          context,
          EmergencyContact(
              name: _f['name']!.text.trim(),
              relationship: _f['rel']!.text.trim(),
              workNumber: _f['work']!.text.trim(),
              homeNumber: _f['home']!.text.trim(),
              mobileNumber: _f['mobile']!.text.trim()));
    } on ArgumentError catch (e) {
      setState(() => _error = '${e.message}');
    }
  }
 
  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: const Text('Add emergency contact'),
      content: Form(
        key: _key,
        child: Column(mainAxisSize: MainAxisSize.min, children: [
          for (final (k, label) in [('name', 'Name'), ('rel', 'Relationship'), ('work', 'Work Number'),
            ('home', 'Home Number'), ('mobile', 'Mobile Number')])
            TextFormField(
              key: Key('ec-$k'),
              controller: _f[k],
              decoration: InputDecoration(labelText: label),
              validator: (v) =>
                  k == 'name' || k == 'rel' ? Validators.required(v, label) : Validators.phone(v),
            ),
          if (_error != null)
            Padding(
              padding: const EdgeInsets.only(top: 8),
              child: Text(_error!, style: const TextStyle(color: Color(0xFFB3261E))),
            ),
        ]),
      ),
      actions: [
        TextButton(onPressed: () => Navigator.pop(context), child: const Text('Cancel')),
        FilledButton(key: const Key('ec-ok'), onPressed: _ok, child: const Text('Add')),
      ],
    );
  }
}
 