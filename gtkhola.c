#include <stdio.h>
#include <gtk/gtk.h>

static void button_clicked( GtkWidget* widget, gpointer data ){
	gtk_label_set_text( (GtkLabel*)data, "Kyaaa~ Baka-senpai desu" );
}

int main (int argc, char *argv[]) {
	gtk_init (&argc, &argv);
	GtkWidget* window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	GtkWidget* button = gtk_button_new_with_label( "Click me Senpai !!" );
	GtkWidget* label = gtk_label_new( "Hello world" );
	GtkWidget* grid = gtk_grid_new();
	g_signal_connect( window, "delete_event",G_CALLBACK(gtk_main_quit), NULL );
	g_signal_connect( button, "clicked", G_CALLBACK( button_clicked ), (gpointer)label );
	//evento de click, uso un puntero a label para modificarlo en la funcion definida
	//arriba, cuando uso G_CALLBACK se llama la funcion con los argumentos button y
	//(gpointer)label
	gtk_grid_attach( (GtkGrid*)grid, button, 1, 1, 1, 1 );
	gtk_grid_attach( (GtkGrid*)grid, label, 1, 2, 1, 1 );
	gtk_grid_set_row_spacing( (GtkGrid*)grid, 12 );
	gtk_grid_set_column_spacing( (GtkGrid*)grid, 12 );
	gtk_grid_set_column_homogeneous( (GtkGrid*)grid, TRUE );
	gtk_grid_set_row_homogeneous( (GtkGrid*)grid, FALSE );
	gtk_window_set_default_size( (GtkWindow*)window, 300, 200 );
	gtk_container_add( (GtkContainer*)window, grid );
	gtk_window_set_title( (GtkWindow*)window, "Hello world" );
	gtk_widget_show_all( window );
	gtk_main();
    return 0;
}
