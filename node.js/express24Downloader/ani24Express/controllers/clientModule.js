(function() {
    window.ClientModule = {
      socket : null,
      fileList : null, //fileInfoList
      fileCount : 0,          //현재 다운받는 것의 갯수

      // 초기화 시에 /chat uri 네임스페이스를 넣어주었다
      initialize : function() {
          this.socket = io.connect("http://localhost:3000");
          window.ClientModule.fileList = new Array();

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

      makeStringFromData : function ( data )
      {
        return '<div class="list-group-item" >'
                + data.fileName + " : " +
                '<div class="progress"><div class="progress-bar" role="progressbar" aria-valuenow="'
                 + data.progress +
                 '" aria-valuemin="0" aria-valuemax="100" style="width:' +
                 data.progress + '%" id=' + data.idx + '>'
                 + data.progress + ' % </div>' + '</div>';
      },

      add : function( data ) {
        console.log( "add request" );
        console.log( data.fileName );

        var fileInfo = new Object();

        fileInfo.idx      = data.idx;
        fileInfo.fileName = data.fileName;
        fileInfo.progress = data.progress;

        window.ClientModule.fileList.push( fileInfo )
        window.ClientModule.fileCount = window.ClientModule.fileCount + 1;
        $('#downNum').text( window.ClientModule.fileCount );
        $('#fileList').append( window.ClientModule.makeStringFromData( data ) );
      },

      updateProgress: function( data ){
        window.ClientModule.fileList.some( function( item, index, array ) {
          console.log( "item.idx : " + item.idx );
          if ( item.idx == data.idx )
          {
            console.log( "idx found : " + data.idx );
            item.progress = data.progress;
            return true;
          }
          else {
            return false;
          }
        })
      },

      // 서버로 부터 발행된 new 이벤트 처리하는 펑션
      progress : function( data ) {
        console.log( "Progress : " + data.progress + ", idx : " + data.idx );
        window.ClientModule.updateProgress( data );
        $('#'+data.idx).text( data.progress + ' %' );
        $('#'+data.idx).attr( "style", 'width: ' + data.progress + '%' );
      },

      send : function() {
          this.socket.emit('downFile', { url: $('#url').val(), progress: 0 } );
          $('#url').val('');
      },
      clear : function() {
          //this.socket.emit('removeFile');
          var removeList = window.ClientModule.fileList.filter( function ( item,index,array ) {
            return item.progress == 100;
          });
          window.ClientModule.fileList =
              window.ClientModule.fileList.filter( function ( item,index,array ) {
                return item.progress != 100;
              });
          console.log( window.ClientModule.fileList );

          $('#downNum').text( window.ClientModule.fileList.length );

          for ( item in removeList )
          {
            $('#'+item.idx).empty();
          }

      }
    };
}());
