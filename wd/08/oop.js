import { Student } from "./Student.js";

import { StudentService } from "./studentService.js";



const service = new StudentService();



service.addStudent(new Student("Dan", 90));

service.addStudent(new Student("Noa", 100));



service.showStudents(student => {

    console.log(student.name, student.grade);

});