const getUsersBtn = document.getElementById("getUsersBtn");
const usersList = document.getElementById("usersList");
getUsersBtn.addEventListener("click", async () => {
  usersList.innerHTML = "";
  const response = await fetch("/api/users");
  const users = await response.json();
  //displey IN list
  users.forEach(user => {
    const li = document.createElement("li");
    li.textContent = `${user.name} - ${user.email} - ${user.role}`;
    usersList.appendChild(li);
  });
});