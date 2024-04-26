let target = "";

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
  apiPost("oled", 'input_display');
}

async function buzzerSet() {
  apiPost("speaker", 'buzzField');
}

async function buzzerStop() {
  apiPost("speaker", 'buzzerStop');
}

async function setLed() {
  apiPost("led", 'ledField');
}

async function photoGet() {
  data = await apiPost("recv_photoresistance", "photoField");
  if (target === "esp1&esp2") {
    esp1 = await apiGet("send_photoresistance_1");
    esp2 = await apiGet("send_photoresistance_2");
    document.getElementById("result_esp1_p").innerHTML = esp1.value;
    return document.getElementById("result_esp2_p").innerHTML = esp2.value;
  }
  else {
    esp = await apiGet("send_photoresistance");
    console.log(esp)
    return document.getElementById("result_"+target+"_p").innerHTML = esp.value;
  }
}

async function buttonGet() {
  data = await apiPost("recv_button", "buttonField");
  if (target === "esp1&esp2") {
    esp1 = await apiGet("send_button_1");
    esp2 = await apiGet("send_button_2");
    document.getElementById("result_esp1_b").innerHTML = esp1.value;
    return document.getElementById("result_esp2_b").innerHTML = esp2.value;
  }
  else {
    esp = await apiGet("send_button");
    console.log(esp);
    return document.getElementById("result_"+target+"_b").innerHTML = esp.value;
  }
}

async function apiPost(topic, id) {
  const html_element = document.getElementById(id);
  if (target === "") {
    console.log("No Target");
    document.getElementById("error").style = "color: firebrick;";
    return document.getElementById("error").innerHTML = "Please select at least one ESP";
  }
  if (target === "esp1") {
    const res = await fetch("/input_user", {
      method: "POST",
      body: JSON.stringify({ topic: topic + "_1", val: html_element.value }).trim()
    });
    console.log(res);
    const data = await res.json();
    return data;
  }
  else if (target === "esp2") {
    const res = await fetch("/input_user", {
      method: "POST",
      body: JSON.stringify({ topic: topic + "_2", val: html_element.value })
    });
    const data = await res.json();
    return data;
  }
  else {
    const res = await fetch("/input_user", {
      method: "POST",
      body: JSON.stringify({ topic: topic + "_1", val: html_element.value }) +
        JSON.stringify({ topic: topic + "_2", val: html_element.value })
    });
    const data = await res.json();
    return data;
  }
}

async function apiGet(topic) {
  if (target === "esp1") {
    const res = await fetch("/request_user/" + topic + "_1", {
      method: 'GET',
      headers: {
        'Content-Type': 'text/json'
      }
    });
    const data = await res.json();
    return data;
  }
  else if (target === "esp2") {
    const res = await fetch("/request_user/" + topic + "_2", {
      method: 'GET', 
      headers: {
        'Content-Type': 'text/json'
      }
    });
    const data = await res.json();
    return data;
  }
  else {
    const res = await fetch("/request_user/" + topic , {
      method: 'GET',
      headers: {
        'Content-Type': 'text/json'
      }
    });
    const data = await res.json();
    return data;
  }
}
