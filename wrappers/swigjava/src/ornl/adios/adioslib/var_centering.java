/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.10
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package ornl.adios.adioslib;

public enum var_centering {
  point(adioslibJNI.point_get()),
  cell(adioslibJNI.cell_get());

  public final int swigValue() {
    return swigValue;
  }

  public static var_centering swigToEnum(int swigValue) {
    var_centering[] swigValues = var_centering.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (var_centering swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + var_centering.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private var_centering() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private var_centering(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private var_centering(var_centering swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}
