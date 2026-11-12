// חוזה נתונים — ממשק
abstract interface class TaskRepository {
  Future<List<Task>> load();
  Future<void> save(List<Task> tasks);
}

// מימוש מקומי עם SharedPreferences
class PreferencesTaskRepository implements TaskRepository {
  PreferencesTaskRepository(this._prefs);
  final SharedPreferencesAsync _prefs;
  static const _key = 'tasks';

  @override
  Future<List<Task>> load() async {
    final raw = await _prefs.getString(_key);
    if (raw == null) return [];
    final list = jsonDecode(raw) as List;
    return list.map((e) => Task.fromJson(e)).toList();
  }

  @override
  Future<void> save(List<Task> tasks) =>
      _prefs.setString(_key, jsonEncode(tasks.map((t) => t.toJson()).toList()));
}