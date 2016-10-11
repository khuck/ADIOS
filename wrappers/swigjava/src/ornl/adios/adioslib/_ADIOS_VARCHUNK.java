/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package ornl.adios.adioslib;

public class _ADIOS_VARCHUNK {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected _ADIOS_VARCHUNK(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(_ADIOS_VARCHUNK obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        adioslibJNI.delete__ADIOS_VARCHUNK(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setVarid(int value) {
    adioslibJNI._ADIOS_VARCHUNK_varid_set(swigCPtr, this, value);
  }

  public int getVarid() {
    return adioslibJNI._ADIOS_VARCHUNK_varid_get(swigCPtr, this);
  }

  public void setType(ADIOS_DATATYPES value) {
    adioslibJNI._ADIOS_VARCHUNK_type_set(swigCPtr, this, value.swigValue());
  }

  public ADIOS_DATATYPES getType() {
    return ADIOS_DATATYPES.swigToEnum(adioslibJNI._ADIOS_VARCHUNK_type_get(swigCPtr, this));
  }

  public void setFrom_steps(int value) {
    adioslibJNI._ADIOS_VARCHUNK_from_steps_set(swigCPtr, this, value);
  }

  public int getFrom_steps() {
    return adioslibJNI._ADIOS_VARCHUNK_from_steps_get(swigCPtr, this);
  }

  public void setNsteps(int value) {
    adioslibJNI._ADIOS_VARCHUNK_nsteps_set(swigCPtr, this, value);
  }

  public int getNsteps() {
    return adioslibJNI._ADIOS_VARCHUNK_nsteps_get(swigCPtr, this);
  }

  public void setSel(SWIGTYPE_p_ADIOS_SELECTION value) {
    adioslibJNI._ADIOS_VARCHUNK_sel_set(swigCPtr, this, SWIGTYPE_p_ADIOS_SELECTION.getCPtr(value));
  }

  public SWIGTYPE_p_ADIOS_SELECTION getSel() {
    long cPtr = adioslibJNI._ADIOS_VARCHUNK_sel_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ADIOS_SELECTION(cPtr, false);
  }

  public void setData(SWIGTYPE_p_void value) {
    adioslibJNI._ADIOS_VARCHUNK_data_set(swigCPtr, this, SWIGTYPE_p_void.getCPtr(value));
  }

  public SWIGTYPE_p_void getData() {
    long cPtr = adioslibJNI._ADIOS_VARCHUNK_data_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public _ADIOS_VARCHUNK() {
    this(adioslibJNI.new__ADIOS_VARCHUNK(), true);
  }

}