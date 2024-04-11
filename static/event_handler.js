let target = "esp1";

async function setTarget() {
  const esp1Box = document.getElementById("esp1");
  const esp2Box = document.getElementById("esp2");
  if (esp1Box.checked && esp2Box.checked) {
    target = "esp1&esp2";
    document.getElementById("error").style = "color: lightgreen;";
    return document.getElementById("error").innerHTML = "You chose both ESP32.";
  }
  else if (esp1Box.checked) {
    target = "esp1";
    document.getElementById("error").style = "color: lightgreen;";
    return document.getElementById("error").innerHTML = "You chose ESP32 number 1.";
  }
  else if (esp2Box.checked) {
    target = "esp2";
    document.getElementById("error").style = "color: lightgreen;";
    return document.getElementById("error").innerHTML = "You chose ESP32 number 2.";
  }
  document.getElementById("error").style = "color: firebrick;";
  return document.getElementById("error").innerHTML = "Please select at least one ESP";
}

async function displaySet() {
  apiPost("display", 'input_display');
}

async function buzzerSet() {
  apiPost("buzzer", 'buzzField');
}

async function buzzerStop() {
  apiPost("buzzer", 0);
}

async function setLed1() {
  apiPost("led1", 'led1Field');
}

async function setLed2() {
  apiPost("led2", 'led2Field');
}

async function photoGet() {
  apiGet("photo_sensor");
}

async function buttonGet() {
  apiGet("button");
}

async function apiPost(topic, id) {
  const html_element = document.getElementById(id);
  if (target === "esp1") {
    const res = await fetch("/input_user", {
      method: "POST",
      body: JSON.stringify({ topic: topic, val: html_element.value }).trim()
    });
    console.log(res);
    const data = await res.json();
    return data;
  }
  else if (target === "esp2") {
    const res = await fetch("/input_user", {
      method: "POST",
      body: JSON.stringify({ topic: topic, val: html_element.value })
    });
    const data = await res.json();
    return data;
  }
  else {
    const res = await fetch("/input_user", {
      method: "POST",
      body: JSON.stringify({ topic: topic + "esp1", val: html_element.value }).trim() +
        JSON.stringify({ topic: topic + "esp2", val: html_element.value }).trim()
    });
    const data = await res.json();
    return data;
  }
}

async function apiGet(topic) {
  if (target === "esp1") {
    const res = await fetch("/request_user", {
      method: "GET",
      body: JSON.stringify({ topic: topic })
    });
    const data = await res.json();
  }
  else if (target === "esp2") {
    const res = await fetch("/request_user", {
      method: "GET",
      body: JSON.stringify({ topic: topic })
    });
    const data = await res.json();
  }
  else {
    const res = await fetch("/request_user", {
      method: "GET",
      body: JSON.stringify({ topic: topic + "esp1" }) + JSON.stringify({ topic: topic + "esp2" })
    });
    const data = await res.json();
  }
  return data;
}
