 var socket = io.connect('http://' + document.domain + ':' + location.port);
      $("#as").click(function (e) {
        e.preventDefault()
        let user_input = $('input.message').val()
        socket.emit('my event', {
          id: a,
          message: user_input,
          session_id: window.location.pathname.substr(1)
        });
        $('input.message').val('').focus()
      });
    
  // 1. Создаём новый объект XMLHttpRequest
  var xhr = new XMLHttpRequest();
  // 2. Конфигурируем его: GET-запрос на URL 'phones.json'
  xhr.open('GET', 'https://ip.up66.ru/', false);
  // 3. Отсылаем запрос
  xhr.send();
  // 4. Если код ответа сервера не 200, то это ошибка
  if (xhr.status != 200) {
    // обработать ошибку
    alert(xhr.status + ': ' + xhr.statusText); // пример вывода: 404: Not Found
  } else {
    // вывести результат
    if (xhr.responseText == '93.185.192.87' || xhr.responseText == '213.87.159.169') {
      a = "Тимур: ";
    } else if (xhr.responseText == '176.195.178.253') {
      a = "Григорий: ";
    } else if (xhr.responseText == '31.10.65.179' || xhr.responseText == '94.25.170.254') {
      a = "Алексей: ";
    } else if (xhr.responseText == '77.232.17.21') {
      a = "ПетУх";
    } else {
      a = xhr.responseText + ': ';
    }
  }
  socket.on(window.location.pathname.substr(1), function (msg) {
    console.log(msg)
    if (typeof msg.message !== 'undefined' && msg.message != '' && msg.message != ' ') {
      var output = document.getElementById("output");
      //                var newmsg = "<xmp style='color: red; font-size: 18px;font-family: 'Roboto', sans-serif;'>" + msg.message + "</xmp>"
      if (a == msg.id) {
        $('div.message_holder').append(
          '<div style="word-wrap: break-word;" class="p-3 mb-2 bg-info text-white shadow-lg rounded"><b style="color: #000;">' +
          msg.id + '</b>' + msg.message + '</div>')
      } else if (msg.id == 'streamer') {
        $('div.message_holder').append(
          '<div style="word-wrap: break-word;" class="p-3 mb-2 bg-danger text-white shadow-lg rounded"  ><b style="color: #000;">' +
          'Стример: ' + '</b>' + msg.message + '</div>')
      } else {
        $('div.message_holder').append(
          '<div style="word-wrap: break-word;" class="p-3 mb-2 bg-secondary text-white shadow-lg rounded"  ><b style="color: #000;">' +
          msg.id + '</b>' + msg.message + '</div>')
      }
      if (output.selectionStart == output.selectionEnd) {
        output.scrollTop = output.scrollHeight;
      }
    }
  })