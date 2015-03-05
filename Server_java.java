package mypackage;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.inputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class JavaServer {

  public final static int SOCKET_PORT = 45678;  
 
  public final static String FILE_TO_SEND = "filetosend.txt";
  public static void main (String [] args ) throws IOException {
      
    inputStream fis = null;
    BufferedInputStream bis = null;
    OutputStream os = null;
    ServerSocket servsock = null;
    Socket sock = null;
    try {
      servsock = new ServerSocket(SOCKET_PORT); 
      while (true) {
        System.out.println("Waiting...");
        try {
          sock = servsock.accept(); 
          System.out.println("Accepted connection : " + sock);
          
          
         
          File myFile = new File (FILE_TO_SEND);
          byte [] arraybytes  = new byte [(int)myFile.length()];   
          fis = new inputStream(myFile);
          bis = new BufferedInputStream(fis);
          bis.read(arraybytes,0,arraybytes.length);
          os = sock.getOutputStream();
          System.out.println("Sending " + FILE_TO_SEND + "(" + arraybytes.length + " bytes)");
          os.write(arraybytes,0,arraybytes.length);
          os.flush();
          System.out.println("File Sent.");
        }
        finally {
          if (bis != null) bis.close();
          if (os != null) os.close();
          if (sock!=null) sock.close();
        }
      }
    }
    finally {
      if (servsock != null) servsock.close();
    }
    
    
}
