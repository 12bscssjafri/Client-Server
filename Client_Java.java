package mypackage;


import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;


public class JavaClient {

  public final static int SOCKET_PORT = 55556;      
  public final static String SERVER = "localhost";  // localhost
  public final static String
       FILE_TO_RECEIVED = "fromjavaclient.txt";   

  public final static int FILE_SIZE = 500000; // file size assumed, it should larger than the file to be transferred

  public static void main (String [] args ) throws IOException {
    int bytesRead;
    int current = 0;
    FileOutputStream fos = null;
    BufferedOutputStream bos = null;
    Socket sock = null;
    try {
      sock = new Socket(SERVER, SOCKET_PORT);//creating socket
      System.out.println("Connecting...");

      
      byte [] mybytearray  = new byte [FILE_SIZE];
      InputStream is = sock.getInputStream();
      fos = new FileOutputStream(FILE_TO_RECEIVED);
      bos = new BufferedOutputStream(fos);
      bytesRead = is.read(mybytearray,0,mybytearray.length); //read file from server store it in bytesRead
      current = bytesRead;

      do {
         bytesRead =
            is.read(mybytearray, current, (mybytearray.length-current));
         if(bytesRead >= 0) current += bytesRead;
      } while(bytesRead > -1);

      bos.write(mybytearray, 0 , current);  //writing to the output stream
      bos.flush();
      System.out.println("File " + FILE_TO_RECEIVED
          + " downloaded (" + current + " bytes read)");
    }
    finally {
      if (fos != null) fos.close();
      if (bos != null) bos.close();
      if (sock != null) sock.close();
    }
  }

}
