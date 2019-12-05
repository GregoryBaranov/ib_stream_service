$('div.test').append('<a class="navbar-brand text-white"> Session\'s ID: ' + window.location.pathname.substr(1) + '</a>')
var socket = io.connect('http://' + document.domain + ':' + location.port);
$("#as").click(function (e) {
  e.preventDefault()
  let user_input = $('input.message').val()
  socket.emit('my event', {
    id: $.cookie("Cookie"),
    message: user_input,
    session_id: window.location.pathname.substr(1)
  });
  $('input.message').val('').focus()
});

socket.on(window.location.pathname.substr(1), function (msg) {
  console.log(msg)
  console.log(Temp)
  if (Temp == 1) {
    $("#supa").hide();
  }
  if (Temp == 0) {
    $("#supa").toggle();
    $("#supa").show();
  }
  if (typeof msg.message !== 'undefined' && msg.message != '' && msg.message != ' ') {
    var output = document.getElementById("output");
    if (msg.id == 'streamer') {
      $('div.message_holder').append(
        '<div style="word-wrap: break-word;" class="p-3 mb-2 bg-danger text-white rounded"  ><b style="color: #000;">' +
        'Стример: ' + '</b>' + msg.message + '</div>')
    } else {
      $('div.message_holder').append(
        '<div style="word-wrap: break-word;" class="p-3 mb-2 bg-info text-white rounded"><b style="color: #000;">' +
        msg.id + ': </b>' + msg.message + '</div>')
    }

    if (output.selectionStart == output.selectionEnd) {
      output.scrollTop = output.scrollHeight;
    }
  }
})

Temp = 0;
$(document).ready(function () {
  function scrollToBottom() {
    $('#output').scrollTop($('#output')[0].scrollHeight);
  }
  $("#output").change(function () {
    scrollToBottom();
  });
  $("#btn").click(function () {
    $("#supa").hide();
    $("#Create").toggle();
    if (Temp == 0) {
      Temp = 1;
    } else {
      Temp = 0;
    }
    $('#output').scrollTop($('#output')[0].scrollHeight);
  });
});

$("#supa").hide();
$("#Create").hide();