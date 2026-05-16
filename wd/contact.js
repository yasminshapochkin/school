
let btn_send = document.querySelector('#btn_send');
let input_b = document.querySelectorAll('#input_b');



btn_send.addEventListener('click' , red_all);

// trim removes white spaces


function red_all(){
    let aler = false;
    // get all input boxes
   // let input_b = document.querySelectorAll('#input_b');
    // run in a loop
    input_b.forEach(element => {
       // see if input boxes have input inside them or not
        if(element.value.trim() === ""){
            element.style.border = "1px solid red";
            aler = true;
            console.log("err?");
    
        } 
        else {
            element.style.border = ""; 
        }
    });
    if(aler == true){
        alert("ALERT");
    }
}

