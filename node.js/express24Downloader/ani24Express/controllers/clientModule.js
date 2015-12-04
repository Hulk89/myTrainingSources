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
        console.log( data.fileName );

        $('#downNum').text( parseInt($('#downNum').text()) + 1 );

        //add url and progressbar
        var idx      = data.idx;
        var fileName = data.fileName;
        var progress = data.progress;
        var string = '<div class="list-group-item" >'
                   + fileName + " : " +
                   '<div class="progress"><div class="progress-bar" role="progressbar" aria-valuenow="' + progress +
                   '" aria-valuemin="0" aria-valuemax="100" style="width:'+progress +'%" id=' + idx + '>'
                   + progress + ' % </div>' + '</div>';
        console.log( string );

        $('#fileList').append( string );
      },

      // 서버로 부터 발행된 new 이벤트 처리하는 펑션
      progress : function( data ) {
          var idx      = data.idx;
          var fileName = data.fileName;
          var progress = data.progress;
          console.log( 'progress : ' + progress + "%" );
          console.log( data );
          $('#'+idx).text( progress + ' %' );
          $('#'+idx).attr( "style", 'width: ' + progress + '%' );
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
