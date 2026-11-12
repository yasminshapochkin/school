class TaskController extends ChangeNotifier {
  TaskController(this._repo);
  final TaskRepository _repo;

  List<Task> tasks = [];
  bool loading = false;
  String? error;

  Future<void> load() async {
    loading = true; notifyListeners();
    try {
      tasks = await _repo.load();
      error = null;
    } catch (e) {
      error = 'טעינה נכשלה';
    } finally {
      loading = false; notifyListeners();
    }
  }

  Future<void> add(String title) async {
    final next = [...tasks, Task(id: _id(), title: title)];
    await _repo.save(next);     // שמירה פסימית: קודם שומרים
    tasks = next;               // ואז מעדכנים את המצב
    notifyListeners();
  }
}