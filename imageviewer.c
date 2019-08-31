#include <gtk/gtk.h>

struct application{
	GtkWidget *window;
	GdkPixbuf *icon;

	/*layout*/
	GtkWidget *vpane;
	GtkWidget *hbox;

	GtkWidget *image;

	GtkWidget *open_button;
	GtkWidget *about_button;

	/*return values*/
	int result;
};

struct application app;

static void show_dialog(GtkWidget *widget, gpointer ptr){
	GtkWidget *about_dialog = gtk_about_dialog_new();

	gtk_about_dialog_set_program_name(about_dialog, "ImageViewer");
	gtk_about_dialog_set_version(about_dialog, "1.0");
	gtk_about_dialog_set_website(about_dialog, "http://www.github.com/PromiseMasango");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),"(c) Promise Masango");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog), "ImageViewer is a simple tool to view images.");


	gtk_about_dialog_set_logo(about_dialog,  app.icon);
	gtk_dialog_run(GTK_DIALOG (about_dialog));
	gtk_widget_destroy(about_dialog);

}


static void open_file(GtkWidget *widget, gpointer ptr){
	GtkWidget *dialog = gtk_file_chooser_dialog_new("Select image", app.window, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	GtkFileFilter *filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(filter,"*");

	gtk_file_chooser_add_filter( dialog, filter );

	app.result = gtk_dialog_run( GTK_DIALOG(dialog) );

	if( app.result == GTK_RESPONSE_ACCEPT){
		gtk_image_set_from_file( app.image, gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog) ));
		gtk_widget_set_size_request(app.image, 600,600);

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
	app.icon = gtk_image_get_pixbuf( icon_image );
	gtk_window_set_icon( app.window, app.icon );



	/*layout*/
	app.vpane = gtk_vpaned_new();
	gtk_paned_set_position(app.vpane, 40);

	app.hbox = gtk_hbox_new(TRUE, 1);


	/*image*/
	app.image = gtk_image_new();


	/*button*/
	app.open_button = gtk_button_new_with_label("open file");
	app.about_button = gtk_button_new_with_label("about");

	gtk_box_pack_start_defaults(GTK_BOX (app.hbox), app.open_button);
	gtk_box_pack_start_defaults(GTK_BOX (app.hbox), app.about_button);

	/*arrange widgets*/
	gtk_paned_add1( GTK_PANED(app.vpane), app.hbox );
	gtk_paned_add2( GTK_PANED(app.vpane), app.image );


	/*listen to events*/
	g_signal_connect( GTK_OBJECT(app.window), "delete_event", GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
	g_signal_connect( GTK_OBJECT(app.open_button), "clicked", G_CALLBACK(open_file), NULL);
	g_signal_connect( GTK_OBJECT(app.about_button), "clicked", G_CALLBACK(show_dialog), NULL);


	/*add default image*/
	gtk_image_set_from_file( app.image, "background.png");

	/*add to container*/
	gtk_container_add (GTK_CONTAINER (app.window), app.vpane);

	gtk_widget_show_all(app.window);
	gtk_main();
	return 0;
}
