


let btn_send = document.querySelector('#btn_send');
let input_b = document.querySelectorAll('#input_b');



btn_send.addEventListener('click' , red_all);

// trim removes white spaces


function red_all(){
    let aler = false;
    
    // run in a loop
    input_b.forEach(ipt => {
        let val = ipt.value.trim();
       // see if input boxes have input inside them or not
        if(val === ""){
            ipt.style.border = "1px solid red";
            aler = true;
            // LOG IS PRINTED IN THE DEVELOPER AREA 
            console.log('ALERT');
    
        } 
        else {
            ipt.style.border = ""; 
            console.log(val);
            
        }
    });
    if(aler == true){
        alert("ALERT");
    }
}

