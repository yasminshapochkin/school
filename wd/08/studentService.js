export class StudentService {

 

constructor() {

this.students = [];

}

 

addStudent(student) {

this.students.push(student);

}

 

showStudents(callback) {

 

this.students.forEach(student => {

callback(student);

});

}

}