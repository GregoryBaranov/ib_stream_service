var xhr = new XMLHttpRequest();

        setInterval(sdad, 500)
        setInterval(gett, 500)

        var a = "";


        function gett() {
            if (xhr.responseText != " " && xhr.responseText != a && xhr.responseText != "") {
                output(xhr.responseText);
                a = xhr.responseText;
            }
        }

        function sdad() {
            xhr.open('GET', 'http://pyserverchat.std-864.ist.mospolytech.ru/ismessage', false);
            xhr.send();
        }

        function Send() {

            var input = document.getElementById("input");
            var text = input.value;

            if (text != " " && text != "") {
                xhr.open('GET', 'http://pyserverchat.std-864.ist.mospolytech.ru/sendMessage?text=' + text, false);
                xhr.send();
            }
            document.getElementById('input').value = "";
        }

        function output(message) {
            var output = document.getElementById("output");
            output.value += "Пользователь написал: " + message + "\n";
            if (output.selectionStart == output.selectionEnd) {
                output.scrollTop = output.scrollHeight;
            }


        }



        $(document).ready(function() {


            $("#output").change(function() {
                scrollToBottom();
            });


            $('input').keydown(function(e) {
                if (e.keyCode === 13) {
                    Send();
                }
            });


            $('#temp').hide();

            function scrollToBottom() {
                $('#output').scrollTop($('#output')[0].scrollHeight);
            }


            $('.btn-hide').on('click', function() {
                $('#cont1').slideToggle(700);
                $('#temp').show();

            });


            $('#temp').on('click', function() {
                $('#cont1').slideToggle(700);

                $('#temp').hide();


            });


        });
