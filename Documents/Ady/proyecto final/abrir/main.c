#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <unistd.h>
int main (int argc, char *argv[])
{

  GtkWidget *win = NULL;
  GtkWidget *ventana;
  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);
  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_title (GTK_WINDOW (win), "Hello World");
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);
    ventana=gtk_file_chooser_dialog_new("Abrir",win,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      "Cancelar", GTK_RESPONSE_CANCEL,
				      "Abrir", GTK_RESPONSE_ACCEPT,
				      NULL);
    if(gtk_dialog_run(ventana)==GTK_RESPONSE_ACCEPT)
        {
        char *filename=gtk_file_chooser_get_filename(ventana);
        FILE *fd=fopen("abrir.paint","w+");
        puts(filename);
        if(fd!=0)
            {
                int a=fputs(filename,fd);
                fclose(fd);
                return 1;
            }
        }
    gtk_widget_destroy(ventana);
  /* Enter the main loop */
  //gtk_main ();
  return 0;
}
