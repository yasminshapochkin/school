// server.js


const express = require("express");
const path = require("path");
const fs = require("fs");

const app = express();
const PORT = 3000;

//enable parsing JSON request bodies
//app.use(express.json());

// Serve static files from the "client" directory
// freee accses to all files in the client folder, like index.html, script.js, style.css, etc.
app.use(express.static("client"));


// Define a route for the root URL
app.get("/", (req, res) => {
  res.send("Hello from Node.js Express!");
});

// Start the server and listen on the specified port

app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});



// Define a route for the /test URL
app.get("/test", (req, res) => {
  res.send("test is working...");
});

app.get("/login", (req, res) => {
  res.send("Login page");
});

/*app.get("/home", (req, res) => {
    
});*/

// Clean URL: /about -> client/about.html
app.get("/home", (req, res, next) => {
  //const pageHome = req.params.page;
    // return html filr to user with this path 
  res.sendFile(path.join(__dirname, "client", `home.html`),
   (err) => {
    if (err) next();
  });
});

app.get("/about", (req, res, next) => {
  //const pageHome = req.params.page;
    // return html filr to user with this path 
  res.sendFile(path.join(__dirname, "client", `home.html`),
   (err) => {
    if (err) next();
  });
});


// ========================================
// API - Get All Users
// ========================================
app.get("/api/users", (req, res) => {

  const filePath = path.join(__dirname, "data", "users.json");

  fs.readFile(filePath, "utf8", (err, data) => {

    if (err) {
      return res.status(500).json({
        error: "Failed to read users file"
      });
    }

    const users = JSON.parse(data);
    // return the users data as JSON response
    res.json(users);
  });
});

app.get("/users", (req, res, next) => {
  //const pageHome = req.params.page;
    // return html filr to user with this path 
  res.sendFile(path.join(__dirname, "client", `users.html`),
   (err) => {
    if (err) next();
  });
});




app.use(express.json());
app.use(express.static("client"));

const usersFilePath = path.join(__dirname, "data", "users.json");

// GET users
app.get("/api/users", (req, res) => {
  fs.readFile(usersFilePath, "utf8", (err, data) => {
    if (err) {
      return res.status(500).json({ error: "Failed to read users file" });
    }

    res.json(JSON.parse(data));
  });
});


// POST register new user
app.post("/api/register", (req, res) => {

    // Get the new user data from the request body
  const newUser = req.body;

  fs.readFile(usersFilePath, "utf8", (err, data) => {
    if (err) {
      return res.status(500).json({ error: "Failed to read users file" });
    }

    const users = JSON.parse(data);

    const userToAdd = {
      id: users.length + 1,
      name: newUser.name,
      email: newUser.email,
      role: newUser.role
    };

    users.push(userToAdd);

    fs.writeFile(usersFilePath, JSON.stringify(users, null, 2), (err) => {
      if (err) {
        return res.status(500).json({ error: "Failed to save user" });
      }

      res.status(201).json({
        message: "User registered successfully",
        user: userToAdd
      });
    });
  });
});