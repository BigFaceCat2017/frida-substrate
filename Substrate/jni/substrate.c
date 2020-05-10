#include <stdio.h>
#include "substrate.h"
#include <fcntl.h>
#include <unistd.h>


void* MSFindSymbol(const char * module_name, const char *name){
	return (gpointer) gum_module_find_export_by_name (module_name, name);
}

void* MSFindBase(const char * module_name){
	return (gpointer) gum_module_find_base_address (module_name);
}

void MSHookFunction(void *symbol, void *replace, void **result){
	GumInterceptor * interceptor;
	gum_init_embedded ();
	LOGE ("MSHookFunction (%x, %x, %x)\n", symbol, replace, result);

	interceptor = gum_interceptor_obtain ();

	/* Transactions are optional but improve performance with multiple hooks. */
	gum_interceptor_begin_transaction (interceptor);

	// gum_interceptor_replace (interceptor,
	// (gpointer) gum_module_find_export_by_name (NULL, "open"), replacement_open, NULL);

	gum_interceptor_replace (interceptor,
	(gpointer) symbol, replace, NULL);

	*result = symbol;
	gum_interceptor_end_transaction (interceptor);

}

//hook方法
/*
void* (*olddlsym)(void*  handle, const char*  symbol);
void* newdlsym(void*  handle, const char*  symbol) {
    LOGD("the handle [0x%x] symbol name:%s",handle,symbol);
    return olddlsym(handle, symbol);
}
void* (*olddlopen)(const char* filename, int myflags);
void* newdlopen(const char* filename, int myflags) {
    LOGD("the dlopen name :%s",filename);
    return olddlopen(filename, myflags);
}

int (*old_access)(const char *path, int mode);
static int my_access(const char *path, int mode){
	LOGE("my_access (%s, %x)", path, mode);
	int result = old_access(path, mode);
	LOGE("result : %d", result);
	return result;

}

int main (int argc, char * argv[]){
	MSHookFunction(&dlopen, &newdlopen, &olddlopen);
	MSHookFunction(&dlsym, &newdlsym, &olddlsym);
	access("/data/local/tmp/aa",F_OK);

	access("/sdcard/",F_OK);
	dlopen("/system/lib64/libz.so", RTLD_NOW);
	
	return 0;

}


typedef struct _ExampleListener ExampleListener;
typedef enum _ExampleHookId ExampleHookId;

struct _ExampleListener
{
  GObject parent;

  guint num_calls;
};

enum _ExampleHookId
{
  EXAMPLE_HOOK_OPEN,
  EXAMPLE_HOOK_CLOSE
};

static void example_listener_iface_init (gpointer g_iface, gpointer iface_data);

#define EXAMPLE_TYPE_LISTENER (example_listener_get_type ())
G_DECLARE_FINAL_TYPE (ExampleListener, example_listener, EXAMPLE, LISTENER, GObject)
G_DEFINE_TYPE_EXTENDED (ExampleListener,
                        example_listener,
                        G_TYPE_OBJECT,
                        0,
                        G_IMPLEMENT_INTERFACE (GUM_TYPE_INVOCATION_LISTENER,
                            example_listener_iface_init))

int
main1 (int argc,
      char * argv[])
{
  GumInterceptor * interceptor;
  GumInvocationListener * listener;

  gum_init_embedded ();

  interceptor = gum_interceptor_obtain ();
  listener = g_object_new (EXAMPLE_TYPE_LISTENER, NULL);

  gum_interceptor_begin_transaction (interceptor);
  gum_interceptor_attach (interceptor,
      GSIZE_TO_POINTER (gum_module_find_export_by_name (NULL, "open")),
      listener,
      GSIZE_TO_POINTER (EXAMPLE_HOOK_OPEN));
  gum_interceptor_attach (interceptor,
      GSIZE_TO_POINTER (gum_module_find_export_by_name (NULL, "close")),
      listener,
      GSIZE_TO_POINTER (EXAMPLE_HOOK_CLOSE));
  gum_interceptor_end_transaction (interceptor);

  close (open ("/etc/hosts", O_RDONLY));
  close (open ("/etc/fstab", O_RDONLY));

  g_print ("[*] listener got %u calls\n", EXAMPLE_LISTENER (listener)->num_calls);

  gum_interceptor_detach (interceptor, listener);

  close (open ("/etc/hosts", O_RDONLY));
  close (open ("/etc/fstab", O_RDONLY));

  g_print ("[*] listener still has %u calls\n", EXAMPLE_LISTENER (listener)->num_calls);

  g_object_unref (listener);
  g_object_unref (interceptor);

  gum_deinit_embedded ();

  return 0;
}

static void
example_listener_on_enter (GumInvocationListener * listener,
                           GumInvocationContext * ic)
{
  ExampleListener * self = EXAMPLE_LISTENER (listener);
  ExampleHookId hook_id = GUM_IC_GET_FUNC_DATA (ic, ExampleHookId);

  switch (hook_id)
  {
    case EXAMPLE_HOOK_OPEN:
      g_print ("[*] open(\"%s\")\n", gum_invocation_context_get_nth_argument (ic, 0));
      break;
    case EXAMPLE_HOOK_CLOSE:
      g_print ("[*] close(%d)\n", (int) gum_invocation_context_get_nth_argument (ic, 0));
      break;
  }

  self->num_calls++;
}

static void
example_listener_on_leave (GumInvocationListener * listener,
                           GumInvocationContext * ic)
{
}

static void
example_listener_class_init (ExampleListenerClass * klass)
{
  (void) EXAMPLE_IS_LISTENER;
  (void) glib_autoptr_cleanup_ExampleListener;
}

static void
example_listener_iface_init (gpointer g_iface,
                             gpointer iface_data)
{
  GumInvocationListenerInterface * iface = g_iface;

  iface->on_enter = example_listener_on_enter;
  iface->on_leave = example_listener_on_leave;
}

static void
example_listener_init (ExampleListener * self)
{
}
*/