$(document).ready(function() {
    $.ajax({
        url: "http://localhost:3030/obtenerram"
    }).then(function(data) {
     //   $("#valores").val(data.total);
        //$("#valores").val(data.total);
      $('.greeting-id').append(data.total);
       $('.greeting-content').append(data.libre);
    });
});