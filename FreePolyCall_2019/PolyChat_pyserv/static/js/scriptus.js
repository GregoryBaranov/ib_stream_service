 var socket = io.connect('http://' + document.domain + ':' + location.port);
      $(document).ready(function () {
        function scrollToBottom() {
          $('#output').scrollTop($('#output')[0].scrollHeight);
        }
        $("#output").change(function () {
          scrollToBottom();
        });
        $('#temp').hide();
        $('.btn-hide').on('click', function () {
          $('#cont1').slideToggle(700);
          $('#temp').show();
        });
        $('#temp').on('click', function () {
          $('#cont1').slideToggle(700);
          $('#temp').fadeOut('slow');
        });
      });
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
  window.location.pathname.substr(1)
  $('div.panel-heading').append('<h3 class="panel-title">' + window.location.pathname.substr(1) + '</h3>')

particlesJS("particles-js", {
    "particles": {
      "number": {
        "value": 133,
        "density": {
          "enable": true,
          "value_area": 946.9771699587272
        }
      },
      "color": {
        "value": "#fff"
      },
      "shape": {
        "type": "circle",
        "stroke": {
          "width": 0,
          "color": "#000000"
        },
        "polygon": {
          "nb_sides": 5
        },
        "image": {
          "src": "img/github.svg",
          "width": 100,
          "height": 100
        }
      },
      "opacity": {
        "value": 0.39457382081613634,
        "random": true,
        "anim": {
          "enable": false,
          "speed": 1,
          "opacity_min": 0.1,
          "sync": false
        }
      },
      "size": {
        "value": 3,
        "random": true,
        "anim": {
          "enable": false,
          "speed": 40,
          "size_min": 0.1,
          "sync": false
        }
      },
      "line_linked": {
        "enable": true,
        "distance": 150,
        "color": "#fff",
        "opacity": 0.4,
        "width": 1
      },
      "move": {
        "enable": true,
        "speed": 6,
        "direction": "none",
        "random": false,
        "straight": false,
        "out_mode": "out",
        "bounce": false,
        "attract": {
          "enable": false,
          "rotateX": 600,
          "rotateY": 1200
        }
      }
    },
    "interactivity": {
      "detect_on": "canvas",
      "events": {
        "onhover": {
          "enable": true,
          "mode": "repulse"
        },
        "onclick": {
          "enable": true,
          "mode": "push"
        },
        "resize": true
      },
      "modes": {
        "grab": {
          "distance": 400,
          "line_linked": {
            "opacity": 1
          }
        },
        "bubble": {
          "distance": 400,
          "size": 40,
          "duration": 2,
          "opacity": 8,
          "speed": 3
        },
        "repulse": {
          "distance": 73.08694910712106,
          "duration": 0.4
        },
        "push": {
          "particles_nb": 4
        },
        "remove": {
          "particles_nb": 2
        }
      }
    },
    "retina_detect": true
  });
  var stats, update;
  stats = new Stats;
  stats.setMode(0);
  stats.domElement.style.position = 'absolute';
  count_particles = document.querySelector('.js-count-particles');
  update = function () {
    stats.begin();
    stats.end();
    if (window.pJSDom[0].pJS.particles && window.pJSDom[0].pJS.particles.array) {
      count_particles.innerText = window.pJSDom[0].pJS.particles.array.length;
    }
    requestAnimationFrame(update);
  };
  requestAnimationFrame(update);;