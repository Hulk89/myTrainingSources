(function() {
    window.ClientModule = {
      socket : null,

     // 초기화 시에 /chat uri 네임스페이스를 넣어주었다
      initialize : function() {
          this.socket = io.connect("http://localhost:3000");

          // send 버튼을 누를 경우 실행
          $('#download').click(function() {
              console.log( "Download Button pressed");
              ClientModule.send();
          });
          $('#clear').click(function() {
            ClientModule.clear();
          })
          this.socket.on('progress', this.progress);
          this.socket.on('addUrl', this.add);
      },

      add : function( data ) {
        console.log( "add request" );
        $('#downNum').text( parseInt($('#downNum').text()) + 1 );
        //add url and progressbar
        $('#fileList').append( '<li class="list-group-item" id=' + data['url'] + '>' + data['url'] + '</li>');

      },

      // 서버로 부터 발행된 new 이벤트 처리하는 펑션
      progress : function( data ) {

          var url = data.url;
          var progress = data.progress;
          console.log( 'progress : ' + progress + "%" );
          $('#'+url).text( url + progress );
      },

      send : function() {
          this.socket.emit('downFile', { url: $('#url').val(), progress: 0 } );
          $('#url').val('');
      },
      clear : function() {
          this.socket.emit('removeFile');
          $('#downNum').text( 0 );
      }
    };
}());
