export class Student {



    constructor(name, grade) {

        this.name = name;

        this.grade = grade;

    }



    display() {

        console.log(`${this.name} - ${this.grade}`);

    }

}