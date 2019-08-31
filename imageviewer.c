#include <gtk/gtk.h>

struct application{
	GtkWidget *window;


	/*layout*/
	GtkWidget *vpane;

	GtkWidget *image;
	GtkWidget *button;

	/*return values*/
	int result;
};

struct application app;

static void open_file(GtkWidget *widget, gpointer ptr){
	GtkWidget *dialog = gtk_file_chooser_dialog_new("Select image", app.window, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	GtkFileFilter *filter = gtk_file_filter_new();

	gtk_file_chooser_add_filter( dialog, filter );

	app.result = gtk_dialog_run( GTK_DIALOG(dialog) );

	if( app.result == GTK_RESPONSE_ACCEPT){
		gtk_image_set_from_file( app.image, gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog) ));
		gtk_widget_set_size_request(app.image, 500,300);

	}

	gtk_widget_destroy(dialog);


}


int main( int argv, char *argc[] ){
	/*initialize gtk*/
	gtk_init( &argv, &argc );

	/*window*/
	app.window = gtk_window_new( GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(app.window), "ImageViewer");
	gtk_window_set_default_size(GTK_WINDOW(app.window), 400, 400);
	gtk_window_set_position(GTK_WINDOW(app.window), GTK_WIN_POS_MOUSE);
	gtk_container_set_border_width (GTK_CONTAINER (app.window), 3);
	gtk_window_set_resizable(app.window, TRUE );

	GtkWidget *icon_image = gtk_image_new_from_file("background.png");
	GdkPixbuf *icon = gtk_image_get_pixbuf( icon_image );
	gtk_window_set_icon( app.window, icon );



	/*layout*/
	app.vpane = gtk_vpaned_new();
//	gtk_paned_set_wide_handle(app.vpane, TRUE);
	gtk_paned_set_position(app.vpane, 40);


	/*image*/
	app.image = gtk_image_new();


	/*button*/
	app.button = gtk_button_new_with_label("open file");

	/*arrange widgets*/

	gtk_paned_add1( GTK_PANED(app.vpane), app.button );
	gtk_paned_add2( GTK_PANED(app.vpane), app.image );


	/*listen to events*/
	g_signal_connect( GTK_OBJECT(app.window), "delete_event", GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
	g_signal_connect( GTK_OBJECT(app.button), "clicked", G_CALLBACK(open_file), NULL);



	/*add default image*/
	gtk_image_set_from_file( app.image, "background.png");

	/*add to container*/
	gtk_container_add (GTK_CONTAINER (app.window), app.vpane);

	gtk_widget_show_all(app.window);
	gtk_main();
	return 0;
}
