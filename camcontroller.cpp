#include "camcontroller.h"

#include <QDebug>


static void
ctx_error_func (GPContext*, const char *str, void*)
{
	qDebug() <<   "Contexterror *** " <<str;
}

static void
ctx_status_func (GPContext*, const char *str, void*)
{
	qDebug() <<  str;
}


CamController::CamController(QObject *parent) : QObject(parent)
{
	CameraText text;
	CameraAbilitiesList *al;
	CameraAbilities abilities;
	GPPortInfoList	*portinfolist = NULL;
	const char *port = "usb:";
	GPPortInfo	pi;
	int p;

	CameraList *list;
	gp_list_new(&list);

	m_context = gp_context_new();

	int retval;
	//	gp_list_find_by_name(list, &camIndex, "Sony Alpha-A6000 (Control)");

	gp_context_set_error_func (m_context, ctx_error_func, NULL);
	gp_context_set_status_func (m_context, ctx_status_func, NULL);

	int m;

	qDebug() << "Creating camera...";
	gp_camera_new (&m_camera);


	retval = gp_abilities_list_new (&al);
	if (retval < GP_OK) {
		qFatal("gp_abilities_list_new");
	}

	retval= gp_abilities_list_load (al, m_context);
	if (retval < GP_OK) {
		qFatal("gp_abilities_list_load");
	}

	m = gp_abilities_list_lookup_model (al, "Sony Alpha-A6000 (Control)");
	gp_abilities_list_get_abilities (al, m, &abilities);
	gp_abilities_list_free (al);
	gp_camera_set_abilities (m_camera, abilities);


	if (!portinfolist) {
		/* Load all the port drivers we have... */
		retval = gp_port_info_list_new (&portinfolist);
		if (retval < GP_OK) {
			qFatal("gp_port_info_list_new");
		}
		retval = gp_port_info_list_load (portinfolist);
		if (retval < 0) {
			qFatal("gp_port_info_list_load");
		}
		retval = gp_port_info_list_count (portinfolist);
		if (retval < 0) {
			qFatal("gp_port_info_list_count");
		}
	}


	p = gp_port_info_list_lookup_path (portinfolist, port);
	if (p < GP_OK) {
		qFatal("gp_port_info_list_lookup_path");
	}

	retval = gp_port_info_list_get_info (portinfolist, p, &pi);
	if (retval < GP_OK){
		qFatal("gp_port_info_list_get_info");
	}

	retval = gp_camera_set_port_info (m_camera, pi);
	if (retval < GP_OK){
		qFatal("gp_camera_set_port_info");
	}

	CameraFilePath cameraFilePath;

	qDebug() << "Camera init.  Can take up to 10 seconds.";
	retval = gp_camera_init(m_camera, m_context);

	if (retval != GP_OK) {
		qWarning() << "  Retval of gp_camera_init: " << retval;
	}

	retval = gp_camera_capture(m_camera, GP_CAPTURE_IMAGE, &cameraFilePath,  m_context);
	if (retval != GP_OK) {
		qWarning() << "  Retval of gp_camera_capture: " << retval;
	}

	qDebug() << "Getting information about the driver...";
	gp_camera_get_about (m_camera, &text, m_context);
	qDebug() << text.text;

	qDebug() << "Unrefing camera...";
	gp_camera_unref (m_camera);
}