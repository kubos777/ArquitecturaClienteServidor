import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Cliente02
{
public static void main(String a[])
{
 Socket socket = null;
 //String peticion = "Usuario: Jorge Chávez";
 Scanner sc = new Scanner(System.in);
 String respuesta = null;
 
 System.out.println("Ingresa texto: ");
 String peticion = sc.nextLine();
 
 try
 {
 System.out.println("Me conecto al puerto 8000 del servidor");
 socket = new Socket(a[0],8000);
 System.out.println("Le envio mi peticion: " + peticion);
 DataOutputStream dos = new DataOutputStream( socket.getOutputStream());
 dos.writeUTF(peticion);
 DataInputStream dis = new DataInputStream( socket.getInputStream() );
 respuesta = dis.readUTF();
 System.out.println("El mensaje que me envio el servidor es: " + respuesta);
 dos.close();
 dis.close();
 socket.close();
 }
 catch(IOException e)
 {
 System.out.println("java.io.IOException generada");
 e.printStackTrace();
 }
}
}