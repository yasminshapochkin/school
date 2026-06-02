document.addEventListener("DOMContentLoaded", function () {

    console.log("Page loaded");



    document.getElementById("loadBtn").addEventListener("click", () => loadMovies());



});


//--------------------------------


function loadMovies() {

    const searchInput = document.getElementById("searchInput");
    const searchText = searchInput.value.toLowerCase();
    
    const moviesList = document.getElementById("moviesList");
    moviesList.innerHTML = "<p>Loading movies...</p>";

    fetch("https://ghibliapi.vercel.app/films")
        .then(function (response) {
            return response.json();
        })
        .then(function (movies) {

            const moviesList = document.getElementById("moviesList");

            moviesList.innerHTML = "";

            for (let i = 0; i < movies.length; i++) {

                const movie = movies[i];

                if (!movie.title.toLowerCase().includes(searchText)) {
                    continue;
                }

                const div = document.createElement("div");
                div.className = "movie-card";

                div.innerHTML = `
                    <img src="${movie.image}" alt="${movie.title}">
                    <h3>${movie.title}</h3>
                    <p><b>Director:</b> ${movie.director}</p>
                    <p><b>Release Year:</b> ${movie.release_date}</p>
                    <p><b>Running Time:</b> ${movie.running_time} minutes</p>
                `;

                moviesList.appendChild(div);
            }

        });

}