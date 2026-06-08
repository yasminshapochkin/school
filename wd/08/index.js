//const { use } = require("react");

document.addEventListener("DOMContentLoaded", () => {

    console.log("Page loaded...");

    DemoCallbacks();
    DemoObjectsWithMethoods();

});

function RunWithParam(callback) {

    for (let i = 0; i < 5; i++) {

        callback(i);

    }

}

function Run(callback) {

    for (let i = 0; i < 5; i++) {

        callback();

    }

}


function Test() {

    console.log("Test function called...");


}


 

 

function DemoCallbacks() {

    let t = Test;

    t();
    // can also do 
    // Run(Test);
    Run(Test);

    Run(() => console.log("Hello from callback!"));

    RunWithParam(i => console.log(`Hello from callback with parameter: ${i}`));
    // can also do this if its a one line
   // RunWithParam(i => console.log(`hello from call back!" ${i} `) );

}

function DemoJson(){
    let user={
        name:"gadi",
        email:"gadi@gmail.com",
      //  formatText:() => {  return `name: ${this.name} , Email: ${this.email}` }
    };
    user.name += "shor" ; 
    //user.formatText();

    // WHAT DOES THAT MEANS?
    // this is destructering
    // take Object and extract veriables from 
    // it knows by the name and user 
    let {name,email} = user;


    getObj(user);


   // console.log(user);



}

// it means im already getting only the veriables that im intrested in
// recive params as veriables 
function getObj({name,email}){
    // will it erase it ? yes now its an "xxx"

    //obj.user = "XXX";

    console.log(`Name: ${name}, Email: ${email}`);



}
// obg 
// - fildes is an array
// methood on the array


function DemoObjectsWithMethoods(){
    const classRoomObj = {
        students:[],
        addStudent(student){
            this.students.push(student);
        },
        removeStudent(student){
            this.students = this.students.filter(s => s !== student);
        },
        print(){
            this.students.forEach(student => console.log(student));
        },
        getStudentsAbove(grade){return this.students.filter(s=> s.grade > grade)},
        filterStudents(filterFunc){

            return this.students.filter(filterFunc)
        }

    };
    // run it 

    classRoomObj.addStudent({name:"daviv" , grade:90});
    classRoomObj.addStudent({name:"ben" , grade:89});
    classRoomObj.addStudent({name:"john" , grade:78});
    classRoomObj.print();
    classRoomObj.removeStudent(classRoomObj.students[0]);
    classRoomObj.print();
    classRoomObj.addStudent({name:"beni" , grade:89});
    classRoomObj.addStudent({name:"dan" , grade:40});
    classRoomObj.print();
    let t = classRoomObj.getStudentsAbove(80);
    t.forEach( student => console.log(student));
    classRoomObj.print();



}



function OOPDemos(){
    
}