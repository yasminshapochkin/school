let btnFetch = document.getElementById("btnFetch");

btnFetch.addEventListener("click", () => {

    //Fetch API

    fetch('https://jsonplaceholder.typicode.com/todos')

        .then(response => response.json())

        .then(

            todos => {

                console.log(todos);

                console.log(todos[0].title);

                //DisplayUI(todos);

            })

        .catch(error => console.error('Error:', error));

});