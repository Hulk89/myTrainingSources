(function() {
    window.ClientModule = {
      socket : null,
      fileList : []
     // 초기화 시에 /chat uri 네임스페이스를 넣어주었다
      initialize : function() {
          this.socket = io.connect("http://localhost:3000");

   // send 버튼을 누를 경우 실행
          $('#download').click(function() {
              console.log( "Download Button pressed");
              ClientModule.send();
          });

          // 서버로 부터 new 이벤트가 오면 메세지를 추가하는 add 콜백 설정
          this.socket.on('progress', this.progress);
      },

      // 서버로 부터 발행된 new 이벤트 처리하는 펑션
      progress : function( data ) {

          var url = data.url;
          var progress = data.progress;
          console.log( 'progress : ' + progress + "%" );
      },

      send : function() {
          this.socket.emit('downFile', {
              url: $('#url').val(),
              progress: 0
          });

          $('#url').val('');
          fileList
      }
    };
}());
