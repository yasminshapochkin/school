const registerForm = document.getElementById("registerForm");
const message = document.getElementById("message");

registerForm.addEventListener("submit", async (event) => {
  event.preventDefault();

  const user = {
    name: document.getElementById("name").value,
    email: document.getElementById("email").value,
    role: document.getElementById("role").value
  };

  const response = await fetch("/api/register", {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify(user)
  });

  const result = await response.json();

  if (response.ok) {
    message.textContent = result.message;
    registerForm.reset();
  } else {
    message.textContent = result.error;
  }
});