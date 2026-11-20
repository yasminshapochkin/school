import 'package:material_ui/material_ui.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:employee_card/main.dart';
 
void main() {
  DateTime fixedToday() => DateTime(2005, 12, 1);
 
  Future<void> pump(WidgetTester t) async {
    t.view.physicalSize = const Size(1600, 2000);
    t.view.devicePixelRatio = 1;
    addTearDown(t.view.reset);
    await t.pumpWidget(EmployeeCardApp(today: fixedToday));
  }
 
  testWidgets('loads Simon Phillips with computed age and service', (t) async {
    await pump(t);
    expect(find.text('Simon Phillips'), findsOneWidget);
    expect(find.text('Age: 26'), findsOneWidget);
    expect(find.text('Length of service\n1 Years 0 Months 20 Days'), findsOneWidget);
    // Add Picture disabled because a photo exists
    expect(t.widget<OutlinedButton>(find.byKey(const Key('add-pic'))).onPressed, isNull);
  });
 
  testWidgets('maiden name enabled only for married women', (t) async {
    await pump(t);
    TextFormField maiden() => t.widget<TextFormField>(find.byKey(const Key('maiden')));
    expect(maiden().enabled, isFalse);
    await t.tap(find.byKey(const Key('sex')));
    await t.pumpAndSettle();
    await t.tap(find.text('female').last);
    await t.pumpAndSettle();
    await t.tap(find.byKey(const Key('marital')));
    await t.pumpAndSettle();
    await t.tap(find.text('married').last);
    await t.pumpAndSettle();
    expect(maiden().enabled, isTrue);
  });
 
  testWidgets('invalid postcode blocks save', (t) async {
    await pump(t);
    await t.enterText(find.byKey(const Key('postcode')), '12345');
    await t.tap(find.byKey(const Key('save')));
    await t.pumpAndSettle();
    expect(find.text('Invalid UK postcode'), findsOneWidget);
    expect(find.text('Please correct the highlighted fields'), findsOneWidget);
  });
 
  testWidgets('save valid card and add emergency contact', (t) async {
    await pump(t);
    await t.tap(find.byKey(const Key('add-contact')));
    await t.pumpAndSettle();
    await t.enterText(find.byKey(const Key('ec-name')), 'Linda Phillips');
    await t.enterText(find.byKey(const Key('ec-rel')), 'Mother');
    await t.enterText(find.byKey(const Key('ec-mobile')), '07700 900777');
    await t.tap(find.byKey(const Key('ec-ok')));
    await t.pumpAndSettle();
    expect(find.text('Linda Phillips'), findsOneWidget);
    await t.tap(find.byKey(const Key('save')));
    await t.pumpAndSettle();
    expect(find.text('Saved: Employee #1 Simon Phillips (Electrician)'), findsOneWidget);
  });
}