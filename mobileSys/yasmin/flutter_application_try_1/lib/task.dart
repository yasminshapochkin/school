class Task {
  const Task({required this.id, required this.title, this.done = false});
  final String id;
  final String title;
  final bool done;

  Task copyWith({String? title, bool? done}) => Task(
    id: id,
    title: title ?? this.title,
    done: done ?? this.done,
  );

  factory Task.fromJson(Map<String, dynamic> j) => Task(
    id: j['id'] as String,
    title: j['title'] as String,
    done: j['done'] as bool,
  );

  Map<String, dynamic> toJson() => {'id': id, 'title': title, 'done': done};
}