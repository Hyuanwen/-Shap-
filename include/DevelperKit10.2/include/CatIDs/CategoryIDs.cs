/*
COPYRIGHT 2006 ESRI

TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL 
Unpublished material - all rights reserved under the 
Copyright Laws of the United States and applicable international 
laws, treaties, and conventions. 

For additional information, contact: 
Environmental Systems Research Institute, Inc. 
Attn: Contracts and Legal Services Department 
380 New York Street 
Redlands, California, 92373 
USA 

email: contracts@esri.com 
*/

// .NET assembly for ESRI-defined Category IDs

using System;
using Microsoft.Win32;

/// <summary>Registers or unregisters classes in ESRI component categories.</summary>
#if _ADF
namespace ESRI.ArcGIS.ADF.CATIDs
#elif _UTILITY
namespace ESRI.ArcGIS.Utility.CATIDs
#else
public class CATIDs
#endif
{

  /// <summary>This class is used internally by the classes in this namespace.</summary>
  public abstract class CatReg
  {

    /// <summary>Registers a class to a component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    /// <param name="CATID">The CATID of the component category to which a class should be registered.</param>
    internal static void Reg(String CLSID, String CATID)
    {
      Registry.ClassesRoot.CreateSubKey(CLSID.Substring(18) + "\\Implemented Categories\\" + CATID);
    }

    /// <summary>Unregisters a class from a component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    /// <param name="CATID">The CATID of the component category from which a class should be unregistered.</param>
    internal static void Unreg(String CLSID, String CATID)
    {
      Registry.ClassesRoot.DeleteSubKey(CLSID.Substring(18) + "\\Implemented Categories\\" + CATID, false);
    }
  }

#if ! _ARC_EXPLORER

  /// <summary>Registers or unregisters a class to the DDEditorExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DEditorExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDEditorExtensions : CatReg
  {

    /// <summary>Registers a class to the DDEditorExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5431E9DA-782E-42FD-9DF3-D3A71A1BD1A4}");}

    /// <summary>Unregisters a class from the DDEditorExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5431E9DA-782E-42FD-9DF3-D3A71A1BD1A4}");}
  }

  /// <summary>Registers or unregisters a class to the DDEditorPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DEditorPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDEditorPropertyPages : CatReg
  {

    /// <summary>Registers a class to the DDEditorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{12EB2053-1F2C-4FBA-A3B8-63369A4A6685}");}

    /// <summary>Unregisters a class from the DDEditorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{12EB2053-1F2C-4FBA-A3B8-63369A4A6685}");}
  }

  /// <summary>Registers or unregisters a class to the DDExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDExtensions : CatReg
  {

    /// <summary>Registers a class to the DDExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A1523ADD-FB91-11D4-80FC-00C04FA0ADF8}");}

    /// <summary>Unregisters a class from the DDExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A1523ADD-FB91-11D4-80FC-00C04FA0ADF8}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionAnnotationTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionAnnotationTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionAnnotationTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionAnnotationTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5BA362E2-100F-43FA-992D-5BA50E8FEEFC}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionAnnotationTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5BA362E2-100F-43FA-992D-5BA50E8FEEFC}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionCOGOLineTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionCOGOLineTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionCOGOLineTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionCOGOLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C66DF60C-2092-4C54-86C0-C258EB763EE1}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionCOGOLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C66DF60C-2092-4C54-86C0-C258EB763EE1}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionDimensionTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionDimensionTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionDimensionTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionDimensionTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7F72F79E-2D24-4FA9-8DCC-9D75C05B42A0}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionDimensionTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7F72F79E-2D24-4FA9-8DCC-9D75C05B42A0}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionGNLineTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionGNLineTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionGNLineTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionGNLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{807B6341-3140-4610-BB8A-907D493F1BF7}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionGNLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{807B6341-3140-4610-BB8A-907D493F1BF7}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionMultipatchTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionMultipatchTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionMultipatchTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionMultipatchTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{38B142CD-90C4-4D53-AC2D-45811CFB8305}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionMultipatchTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{38B142CD-90C4-4D53-AC2D-45811CFB8305}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionMultipointTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionMultipointTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionMultipointTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionMultipointTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7608DAD4-BF34-419C-B8C6-1B121EAA0600}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionMultipointTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7608DAD4-BF34-419C-B8C6-1B121EAA0600}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionPointTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionPointTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionPointTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionPointTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F5963D2F-A8C8-4B05-A708-A09790832EC3}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionPointTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F5963D2F-A8C8-4B05-A708-A09790832EC3}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionPolygonTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionPolygonTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionPolygonTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionPolygonTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4F019991-9574-41BE-A09C-B6FF84F9B803}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionPolygonTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4F019991-9574-41BE-A09C-B6FF84F9B803}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionPolylineTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionPolylineTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionPolylineTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionPolylineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B4113DD7-80A9-4AEF-888D-A55DF130B62F}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionPolylineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B4113DD7-80A9-4AEF-888D-A55DF130B62F}");}
  }

  /// <summary>Registers or unregisters a class to the DDFeatureConstructionTurnLineTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the 3DFeatureConstructionTurnLineTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDFeatureConstructionTurnLineTools : CatReg
  {

    /// <summary>Registers a class to the DDFeatureConstructionTurnLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6368BA26-CBA4-4098-9D88-33AF58DA348C}");}

    /// <summary>Unregisters a class from the DDFeatureConstructionTurnLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6368BA26-CBA4-4098-9D88-33AF58DA348C}");}
  }

  /// <summary>Registers or unregisters a class to the AdjustmentMethodPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AdjustmentMethodPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AdjustmentMethodPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AdjustmentMethodPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0772EAEC-F5B4-4F2C-BFE8-019861BD3A43}");}

    /// <summary>Unregisters a class from the AdjustmentMethodPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0772EAEC-F5B4-4F2C-BFE8-019861BD3A43}");}
  }

  /// <summary>Registers or unregisters a class to the AdjustmentPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AdjustmentPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AdjustmentPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AdjustmentPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3E15409F-572B-47DE-91C3-7F310CE04F5B}");}

    /// <summary>Unregisters a class from the AdjustmentPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3E15409F-572B-47DE-91C3-7F310CE04F5B}");}
  }

  /// <summary>Registers or unregisters a class to the AGAnimationKeyframePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGAnimationKeyframePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGAnimationKeyframePropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGAnimationKeyframePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{40E36900-0A42-4CB7-8748-2623538D1D85}");}

    /// <summary>Unregisters a class from the AGAnimationKeyframePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{40E36900-0A42-4CB7-8748-2623538D1D85}");}
  }

  /// <summary>Registers or unregisters a class to the AGAnimationPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGAnimationPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGAnimationPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGAnimationPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E0D5ED2C-FD68-4435-A345-0EF45D11DED9}");}

    /// <summary>Unregisters a class from the AGAnimationPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E0D5ED2C-FD68-4435-A345-0EF45D11DED9}");}
  }

  /// <summary>Registers or unregisters a class to the AGAnimationTrackPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGAnimationTrackPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGAnimationTrackPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGAnimationTrackPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{59242FFB-0BBB-49FB-B335-3F0B5756B314}");}

    /// <summary>Unregisters a class from the AGAnimationTrackPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{59242FFB-0BBB-49FB-B335-3F0B5756B314}");}
  }

  /// <summary>Registers or unregisters a class to the AGSCatalogPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSCatalogPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSCatalogPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSCatalogPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{89372E3D-B764-463D-A06E-F78392BF6CCC}");}

    /// <summary>Unregisters a class from the AGSCatalogPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{89372E3D-B764-463D-A06E-F78392BF6CCC}");}
  }

  /// <summary>Registers or unregisters a class to the AGSConnAdminPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSConnAdminPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSConnAdminPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSConnAdminPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FF24A8D2-3D84-498A-857A-8F1401531932}");}

    /// <summary>Unregisters a class from the AGSConnAdminPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FF24A8D2-3D84-498A-857A-8F1401531932}");}
  }

  /// <summary>Registers or unregisters a class to the AGSConnUserPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSConnUserPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSConnUserPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSConnUserPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BF0BA580-58C6-402C-8E85-A88712E26DEF}");}

    /// <summary>Unregisters a class from the AGSConnUserPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BF0BA580-58C6-402C-8E85-A88712E26DEF}");}
  }

  /// <summary>Registers or unregisters a class to the AGSDiscoveryConnAdminPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSDiscoveryConnAdminPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSDiscoveryConnAdminPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSDiscoveryConnAdminPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{32FA5AAA-CF41-49D4-926E-223338F9866F}");}

    /// <summary>Unregisters a class from the AGSDiscoveryConnAdminPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{32FA5AAA-CF41-49D4-926E-223338F9866F}");}
  }

  /// <summary>Registers or unregisters a class to the AGSDiscoveryConnUserPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSDiscoveryConnUserPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSDiscoveryConnUserPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSDiscoveryConnUserPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B2D59DD1-68BE-432C-9C1D-6FCEC70F161F}");}

    /// <summary>Unregisters a class from the AGSDiscoveryConnUserPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B2D59DD1-68BE-432C-9C1D-6FCEC70F161F}");}
  }

  /// <summary>Registers or unregisters a class to the AGSFeaturePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSFeaturePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSFeaturePropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSFeaturePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2BBA1A21-5E3F-41F9-B608-58A761303D83}");}

    /// <summary>Unregisters a class from the AGSFeaturePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2BBA1A21-5E3F-41F9-B608-58A761303D83}");}
  }

  /// <summary>Registers or unregisters a class to the AGSFolderPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSFolderPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSFolderPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSFolderPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BB787DEF-4CC7-4DC2-A8F1-AD1A93D5BFF9}");}

    /// <summary>Unregisters a class from the AGSFolderPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BB787DEF-4CC7-4DC2-A8F1-AD1A93D5BFF9}");}
  }

  /// <summary>Registers or unregisters a class to the AGSGeocodePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSGeocodePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSGeocodePropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSGeocodePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{882BDC69-9C26-419E-BEEF-61C99AD2C6AB}");}

    /// <summary>Unregisters a class from the AGSGeocodePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{882BDC69-9C26-419E-BEEF-61C99AD2C6AB}");}
  }

  /// <summary>Registers or unregisters a class to the AGSGeoDataServerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSGeoDataServerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSGeoDataServerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSGeoDataServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{45EFCD1F-56BE-4D67-888E-C690F56B4FF8}");}

    /// <summary>Unregisters a class from the AGSGeoDataServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{45EFCD1F-56BE-4D67-888E-C690F56B4FF8}");}
  }

  /// <summary>Registers or unregisters a class to the AGSGeometryPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSGeometryPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSGeometryPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSGeometryPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BE4BF931-0F64-4F5C-B2FA-8C70553995B9}");}

    /// <summary>Unregisters a class from the AGSGeometryPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BE4BF931-0F64-4F5C-B2FA-8C70553995B9}");}
  }

  /// <summary>Registers or unregisters a class to the AGSGeoprocessingPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSGeoprocessingPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSGeoprocessingPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSGeoprocessingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{51CD7E6A-7A07-45D5-9C70-694FB2201013}");}

    /// <summary>Unregisters a class from the AGSGeoprocessingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{51CD7E6A-7A07-45D5-9C70-694FB2201013}");}
  }

  /// <summary>Registers or unregisters a class to the AGSGlobeServerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSGlobeServerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSGlobeServerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSGlobeServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0B383534-8C15-4458-A953-B02575BD1834}");}

    /// <summary>Unregisters a class from the AGSGlobeServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0B383534-8C15-4458-A953-B02575BD1834}");}
  }

  /// <summary>Registers or unregisters a class to the AGSImagePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSImagePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSImagePropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSImagePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CC35E6C6-8D16-4F51-BC3E-784E0E4D03E5}");}

    /// <summary>Unregisters a class from the AGSImagePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CC35E6C6-8D16-4F51-BC3E-784E0E4D03E5}");}
  }

  /// <summary>Registers or unregisters a class to the AGSMapPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSMapPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSMapPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSMapPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4B6512F1-6D5A-4A7F-968F-760A01780569}");}

    /// <summary>Unregisters a class from the AGSMapPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4B6512F1-6D5A-4A7F-968F-760A01780569}");}
  }

  /// <summary>Registers or unregisters a class to the AGSParameterPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSParameterPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSParameterPages : CatReg
  {

    /// <summary>Registers a class to the AGSParameterPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EF160A6A-E93D-408B-BEC2-176135550BD2}");}

    /// <summary>Unregisters a class from the AGSParameterPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EF160A6A-E93D-408B-BEC2-176135550BD2}");}
  }

  /// <summary>Registers or unregisters a class to the AGSServerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSServerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSServerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0BA29352-DAF3-49C2-BD4F-D3C32350E955}");}

    /// <summary>Unregisters a class from the AGSServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0BA29352-DAF3-49C2-BD4F-D3C32350E955}");}
  }

  /// <summary>Registers or unregisters a class to the AGSSOEParameterPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSSOEParameterPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSSOEParameterPages : CatReg
  {

    /// <summary>Registers a class to the AGSSOEParameterPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A585A585-B58B-4560-80E3-87A411859379}");}

    /// <summary>Unregisters a class from the AGSSOEParameterPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A585A585-B58B-4560-80E3-87A411859379}");}
  }

  /// <summary>Registers or unregisters a class to the AGSWMServerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AGSWMServerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AGSWMServerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the AGSWMServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{648B551B-CCD4-4D39-8A8E-0741E0402B8D}");}

    /// <summary>Unregisters a class from the AGSWMServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{648B551B-CCD4-4D39-8A8E-0741E0402B8D}");}
  }

  /// <summary>Registers or unregisters a class to the AnimationVideoExporters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AnimationVideoExporters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AnimationVideoExporters : CatReg
  {

    /// <summary>Registers a class to the AnimationVideoExporters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E133E49C-536A-4647-8ED3-63F8DC6016D5}");}

    /// <summary>Unregisters a class from the AnimationVideoExporters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E133E49C-536A-4647-8ED3-63F8DC6016D5}");}
  }

  /// <summary>Registers or unregisters a class to the AnnoEditToolMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AnnoEditToolMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AnnoEditToolMenuCommands : CatReg
  {

    /// <summary>Registers a class to the AnnoEditToolMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{76A8ECAD-B02F-4A89-9EE0-AEA83B5BB2A2}");}

    /// <summary>Unregisters a class from the AnnoEditToolMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{76A8ECAD-B02F-4A89-9EE0-AEA83B5BB2A2}");}
  }

  /// <summary>Registers or unregisters a class to the AnnotationConstructors component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AnnotationConstructors class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AnnotationConstructors : CatReg
  {

    /// <summary>Registers a class to the AnnotationConstructors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7AE18D82-7FA4-4053-97B9-F65627D92FFD}");}

    /// <summary>Unregisters a class from the AnnotationConstructors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7AE18D82-7FA4-4053-97B9-F65627D92FFD}");}
  }

  /// <summary>Registers or unregisters a class to the AnnotationExpresionPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AnnotationExpresionPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AnnotationExpresionPages : CatReg
  {

    /// <summary>Registers a class to the AnnotationExpresionPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F3E803A1-6EC5-11D2-A2C6-080009B6F22B}");}

    /// <summary>Unregisters a class from the AnnotationExpresionPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F3E803A1-6EC5-11D2-A2C6-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the AnnotationExpressionParsers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AnnotationExpressionParsers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AnnotationExpressionParsers : CatReg
  {

    /// <summary>Registers a class to the AnnotationExpressionParsers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{02D588E1-3D42-11D2-A2A2-080009B6F22B}");}

    /// <summary>Unregisters a class from the AnnotationExpressionParsers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{02D588E1-3D42-11D2-A2A2-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the AnnotationPlacementPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AnnotationPlacementPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AnnotationPlacementPages : CatReg
  {

    /// <summary>Registers a class to the AnnotationPlacementPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2B5310E1-6EC9-11D2-A2C6-080009B6F22B}");}

    /// <summary>Unregisters a class from the AnnotationPlacementPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2B5310E1-6EC9-11D2-A2C6-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the AnnotationPlacementPluginPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AnnotationPlacementPluginPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AnnotationPlacementPluginPages : CatReg
  {

    /// <summary>Registers a class to the AnnotationPlacementPluginPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E4EF2AAE-F050-4070-9CDF-8823F4D4992B}");}

    /// <summary>Unregisters a class from the AnnotationPlacementPluginPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E4EF2AAE-F050-4070-9CDF-8823F4D4992B}");}
  }

  /// <summary>Registers or unregisters a class to the AnnotationPropertiesConverters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AnnotationPropertiesConverters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AnnotationPropertiesConverters : CatReg
  {

    /// <summary>Registers a class to the AnnotationPropertiesConverters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6ED8B756-1BAA-12D3-9FB3-00C04F6BB7A6}");}

    /// <summary>Unregisters a class from the AnnotationPropertiesConverters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6ED8B756-1BAA-12D3-9FB3-00C04F6BB7A6}");}
  }

  /// <summary>Registers or unregisters a class to the ArcToolboxTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ArcToolboxTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ArcToolboxTools : CatReg
  {

    /// <summary>Registers a class to the ArcToolboxTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B5E9A20C-0D77-11D4-9FE0-00C04F6BC61D}");}

    /// <summary>Unregisters a class from the ArcToolboxTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B5E9A20C-0D77-11D4-9FE0-00C04F6BC61D}");}
  }

  /// <summary>Registers or unregisters a class to the ArcToolboxViews component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ArcToolboxViews class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ArcToolboxViews : CatReg
  {

    /// <summary>Registers a class to the ArcToolboxViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{318BD39C-284F-4771-8957-8958FD8FA295}");}

    /// <summary>Unregisters a class from the ArcToolboxViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{318BD39C-284F-4771-8957-8958FD8FA295}");}
  }

  /// <summary>Registers or unregisters a class to the AreaBoundaryCoveredByAreaBoundaryErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaBoundaryCoveredByAreaBoundaryErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaBoundaryCoveredByAreaBoundaryErrorCommands : CatReg
  {

    /// <summary>Registers a class to the AreaBoundaryCoveredByAreaBoundaryErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C934A77D-F1ED-4638-848A-121CB3841BC4}");}

    /// <summary>Unregisters a class from the AreaBoundaryCoveredByAreaBoundaryErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C934A77D-F1ED-4638-848A-121CB3841BC4}");}
  }

  /// <summary>Registers or unregisters a class to the AreaContainsOnePointErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaContainsOnePointErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaContainsOnePointErrorCommands : CatReg
  {

    /// <summary>Registers a class to the AreaContainsOnePointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E85A9A2C-8BE1-4DC2-B366-DD09FCBAA61D}");}

    /// <summary>Unregisters a class from the AreaContainsOnePointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E85A9A2C-8BE1-4DC2-B366-DD09FCBAA61D}");}
  }

  /// <summary>Registers or unregisters a class to the AreaContainsPointErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaContainsPointErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaContainsPointErrorCommands : CatReg
  {

    /// <summary>Registers a class to the AreaContainsPointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{24752620-351E-44B2-908F-22BC1969E6F0}");}

    /// <summary>Unregisters a class from the AreaContainsPointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{24752620-351E-44B2-908F-22BC1969E6F0}");}
  }

  /// <summary>Registers or unregisters a class to the AreaCoveredByAreaErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaCoveredByAreaErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaCoveredByAreaErrorCommands : CatReg
  {

    /// <summary>Registers a class to the AreaCoveredByAreaErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DE141B42-A4F1-4D8B-8F39-7126E2F5216D}");}

    /// <summary>Unregisters a class from the AreaCoveredByAreaErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DE141B42-A4F1-4D8B-8F39-7126E2F5216D}");}
  }

  /// <summary>Registers or unregisters a class to the AreaCoverErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaCoverErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaCoverErrorCommands : CatReg
  {

    /// <summary>Registers a class to the AreaCoverErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B8C9D62F-CCA4-4AD6-B7F9-08CBCAA265FD}");}

    /// <summary>Unregisters a class from the AreaCoverErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B8C9D62F-CCA4-4AD6-B7F9-08CBCAA265FD}");}
  }

  /// <summary>Registers or unregisters a class to the AreaGapErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaGapErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaGapErrorCommands : CatReg
  {

    /// <summary>Registers a class to the AreaGapErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B4728E0C-1E64-4504-826C-F39DF8A3123F}");}

    /// <summary>Unregisters a class from the AreaGapErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B4728E0C-1E64-4504-826C-F39DF8A3123F}");}
  }

  /// <summary>Registers or unregisters a class to the AreaOverlapErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaOverlapErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaOverlapErrorCommands : CatReg
  {

    /// <summary>Registers a class to the AreaOverlapErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{697D68A5-8FB3-41B2-AF2C-F74405783AE8}");}

    /// <summary>Unregisters a class from the AreaOverlapErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{697D68A5-8FB3-41B2-AF2C-F74405783AE8}");}
  }

  /// <summary>Registers or unregisters a class to the AreaPatches component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaPatches class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaPatches : CatReg
  {

    /// <summary>Registers a class to the AreaPatches component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F21E3E7B-E3BA-11D2-B868-00600802E603}");}

    /// <summary>Unregisters a class from the AreaPatches component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F21E3E7B-E3BA-11D2-B868-00600802E603}");}
  }

  /// <summary>Registers or unregisters a class to the AreaTessellateErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AreaTessellateErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AreaTessellateErrorCommands : CatReg
  {

    /// <summary>Registers a class to the AreaTessellateErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F90C3728-7DB1-4158-8CBB-A362F7157C81}");}

    /// <summary>Unregisters a class from the AreaTessellateErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F90C3728-7DB1-4158-8CBB-A362F7157C81}");}
  }

  /// <summary>Registers or unregisters a class to the AttributeTransferTypes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AttributeTransferTypes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AttributeTransferTypes : CatReg
  {

    /// <summary>Registers a class to the AttributeTransferTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{51C6C6AB-DACE-49DB-AF63-32F241C35E49}");}

    /// <summary>Unregisters a class from the AttributeTransferTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{51C6C6AB-DACE-49DB-AF63-32F241C35E49}");}
  }

  /// <summary>Registers or unregisters a class to the AVFSrcImporters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AVFSrcImporters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AVFSrcImporters : CatReg
  {

    /// <summary>Registers a class to the AVFSrcImporters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{56BBC8A4-E583-11D3-9FD8-00C04F6BC78E}");}

    /// <summary>Unregisters a class from the AVFSrcImporters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{56BBC8A4-E583-11D3-9FD8-00C04F6BC78E}");}
  }

  /// <summary>Registers or unregisters a class to the AVThemeImporters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the AVThemeImporters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class AVThemeImporters : CatReg
  {

    /// <summary>Registers a class to the AVThemeImporters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{56BBC8A1-E583-11D3-9FD8-00C04F6BC78E}");}

    /// <summary>Unregisters a class from the AVThemeImporters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{56BBC8A1-E583-11D3-9FD8-00C04F6BC78E}");}
  }

  /// <summary>Registers or unregisters a class to the Backgrounds component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the Backgrounds class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class Backgrounds : CatReg
  {

    /// <summary>Registers a class to the Backgrounds component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EB5A6D3A-DE07-11D2-B868-00600802E603}");}

    /// <summary>Unregisters a class from the Backgrounds component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EB5A6D3A-DE07-11D2-B868-00600802E603}");}
  }

  /// <summary>Registers or unregisters a class to the BGL component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGL class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGL : CatReg
  {

    /// <summary>Registers a class to the BGL component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{ABA69297-080C-4DAC-AA6F-3E4DCB8DC532}");}

    /// <summary>Unregisters a class from the BGL component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{ABA69297-080C-4DAC-AA6F-3E4DCB8DC532}");}
  }

  /// <summary>Registers or unregisters a class to the BGL_PRINTER_DRIVERS component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGL_PRINTER_DRIVERS class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGL_PRINTER_DRIVERS : CatReg
  {

    /// <summary>Registers a class to the BGL_PRINTER_DRIVERS component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9F87AD58-F864-4C25-8004-D17DDF4990C0}");}

    /// <summary>Unregisters a class from the BGL_PRINTER_DRIVERS component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9F87AD58-F864-4C25-8004-D17DDF4990C0}");}
  }

  /// <summary>Registers or unregisters a class to the BGLColorRamps component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLColorRamps class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLColorRamps : CatReg
  {

    /// <summary>Registers a class to the BGLColorRamps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{081B5868-8775-4606-A9B8-FC2FB26899BB}");}

    /// <summary>Unregisters a class from the BGLColorRamps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{081B5868-8775-4606-A9B8-FC2FB26899BB}");}
  }

  /// <summary>Registers or unregisters a class to the BGLColors component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLColors class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLColors : CatReg
  {

    /// <summary>Registers a class to the BGLColors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{54418511-BA7E-4636-866C-397D86A4963E}");}

    /// <summary>Unregisters a class from the BGLColors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{54418511-BA7E-4636-866C-397D86A4963E}");}
  }

  /// <summary>Registers or unregisters a class to the BGLCustomOps component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLCustomOps class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLCustomOps : CatReg
  {

    /// <summary>Registers a class to the BGLCustomOps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{01142BBE-0AFE-4441-B2EF-4AF36A707CCF}");}

    /// <summary>Unregisters a class from the BGLCustomOps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{01142BBE-0AFE-4441-B2EF-4AF36A707CCF}");}
  }

  /// <summary>Registers or unregisters a class to the BGLFillOpEffect component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLFillOpEffect class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLFillOpEffect : CatReg
  {

    /// <summary>Registers a class to the BGLFillOpEffect component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B21AE9FB-018D-4B83-91CC-39DF96F4D765}");}

    /// <summary>Unregisters a class from the BGLFillOpEffect component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B21AE9FB-018D-4B83-91CC-39DF96F4D765}");}
  }

  /// <summary>Registers or unregisters a class to the BGLFillOps component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLFillOps class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLFillOps : CatReg
  {

    /// <summary>Registers a class to the BGLFillOps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{90B28B5E-2434-447C-9C14-41715BA27E80}");}

    /// <summary>Unregisters a class from the BGLFillOps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{90B28B5E-2434-447C-9C14-41715BA27E80}");}
  }

  /// <summary>Registers or unregisters a class to the BGLGeometricEffects component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLGeometricEffects class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLGeometricEffects : CatReg
  {

    /// <summary>Registers a class to the BGLGeometricEffects component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A27F1503-F123-4D10-86C3-432C4FF8AF64}");}

    /// <summary>Unregisters a class from the BGLGeometricEffects component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A27F1503-F123-4D10-86C3-432C4FF8AF64}");}
  }

  /// <summary>Registers or unregisters a class to the BGLIMAGEDECODERS component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLIMAGEDECODERS class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLIMAGEDECODERS : CatReg
  {

    /// <summary>Registers a class to the BGLIMAGEDECODERS component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FAB7D910-C5AA-4CD6-AE47-726E18E56AE5}");}

    /// <summary>Unregisters a class from the BGLIMAGEDECODERS component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FAB7D910-C5AA-4CD6-AE47-726E18E56AE5}");}
  }

  /// <summary>Registers or unregisters a class to the BGLIMAGEENCODERS component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLIMAGEENCODERS class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLIMAGEENCODERS : CatReg
  {

    /// <summary>Registers a class to the BGLIMAGEENCODERS component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2A0D3C2A-A198-4819-AF97-ED5E25F14A68}");}

    /// <summary>Unregisters a class from the BGLIMAGEENCODERS component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2A0D3C2A-A198-4819-AF97-ED5E25F14A68}");}
  }

  /// <summary>Registers or unregisters a class to the BGLMarkerPlacements component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLMarkerPlacements class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLMarkerPlacements : CatReg
  {

    /// <summary>Registers a class to the BGLMarkerPlacements component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0EDB51E1-752A-4211-A2EA-66670006A6A4}");}

    /// <summary>Unregisters a class from the BGLMarkerPlacements component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0EDB51E1-752A-4211-A2EA-66670006A6A4}");}
  }

  /// <summary>Registers or unregisters a class to the BGLMarkerSymbols component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLMarkerSymbols class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLMarkerSymbols : CatReg
  {

    /// <summary>Registers a class to the BGLMarkerSymbols component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BA521553-F7B5-4950-AC60-EC2699763526}");}

    /// <summary>Unregisters a class from the BGLMarkerSymbols component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BA521553-F7B5-4950-AC60-EC2699763526}");}
  }

  /// <summary>Registers or unregisters a class to the BGLPaintingOps component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLPaintingOps class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLPaintingOps : CatReg
  {

    /// <summary>Registers a class to the BGLPaintingOps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E3EFE76C-8A0B-40FD-AE64-49E5604C9A38}");}

    /// <summary>Unregisters a class from the BGLPaintingOps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E3EFE76C-8A0B-40FD-AE64-49E5604C9A38}");}
  }

  /// <summary>Registers or unregisters a class to the BGLPatterns component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLPatterns class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLPatterns : CatReg
  {

    /// <summary>Registers a class to the BGLPatterns component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{77D689FE-2979-4517-8259-6465B37F0E61}");}

    /// <summary>Unregisters a class from the BGLPatterns component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{77D689FE-2979-4517-8259-6465B37F0E61}");}
  }

  /// <summary>Registers or unregisters a class to the BGLPRINTERS component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLPRINTERS class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLPRINTERS : CatReg
  {

    /// <summary>Registers a class to the BGLPRINTERS component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{37C8E52F-AA9C-490E-B22C-974582FB5B56}");}

    /// <summary>Unregisters a class from the BGLPRINTERS component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{37C8E52F-AA9C-490E-B22C-974582FB5B56}");}
  }

  /// <summary>Registers or unregisters a class to the BGLSimpleSymbols component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLSimpleSymbols class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLSimpleSymbols : CatReg
  {

    /// <summary>Registers a class to the BGLSimpleSymbols component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{78582C83-2A4F-4B12-88E5-8E6C293DC5FD}");}

    /// <summary>Unregisters a class from the BGLSimpleSymbols component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{78582C83-2A4F-4B12-88E5-8E6C293DC5FD}");}
  }

  /// <summary>Registers or unregisters a class to the BGLStrokeOps component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLStrokeOps class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLStrokeOps : CatReg
  {

    /// <summary>Registers a class to the BGLStrokeOps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{354B72BE-5FDF-4B94-B7A7-F7653D9216B7}");}

    /// <summary>Unregisters a class from the BGLStrokeOps component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{354B72BE-5FDF-4B94-B7A7-F7653D9216B7}");}
  }

  /// <summary>Registers or unregisters a class to the BGLSymbols component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLSymbols class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLSymbols : CatReg
  {

    /// <summary>Registers a class to the BGLSymbols component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DC3250F3-BDBE-42AA-A5C0-5E77A0EB15CE}");}

    /// <summary>Unregisters a class from the BGLSymbols component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DC3250F3-BDBE-42AA-A5C0-5E77A0EB15CE}");}
  }

  /// <summary>Registers or unregisters a class to the BGLTextSymbols component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BGLTextSymbols class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BGLTextSymbols : CatReg
  {

    /// <summary>Registers a class to the BGLTextSymbols component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F552A120-AB8D-49CC-8C23-8B19D6A8A6D5}");}

    /// <summary>Unregisters a class from the BGLTextSymbols component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F552A120-AB8D-49CC-8C23-8B19D6A8A6D5}");}
  }

  /// <summary>Registers or unregisters a class to the Borders component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the Borders class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class Borders : CatReg
  {

    /// <summary>Registers a class to the Borders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EB5A6D39-DE07-11D2-B868-00600802E603}");}

    /// <summary>Unregisters a class from the Borders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EB5A6D39-DE07-11D2-B868-00600802E603}");}
  }

  /// <summary>Registers or unregisters a class to the BoundaryCoincidenceErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BoundaryCoincidenceErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BoundaryCoincidenceErrorCommands : CatReg
  {

    /// <summary>Registers a class to the BoundaryCoincidenceErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{78CEB2AE-E575-4A37-A067-478711A85D15}");}

    /// <summary>Unregisters a class from the BoundaryCoincidenceErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{78CEB2AE-E575-4A37-A067-478711A85D15}");}
  }

  /// <summary>Registers or unregisters a class to the BoundaryCoverErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BoundaryCoverErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BoundaryCoverErrorCommands : CatReg
  {

    /// <summary>Registers a class to the BoundaryCoverErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1C766272-65BB-4F6E-93A5-3F196F5BA59C}");}

    /// <summary>Unregisters a class from the BoundaryCoverErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1C766272-65BB-4F6E-93A5-3F196F5BA59C}");}
  }

  /// <summary>Registers or unregisters a class to the BuildMethods component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the BuildMethods class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class BuildMethods : CatReg
  {

    /// <summary>Registers a class to the BuildMethods component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{16B2A5BC-9805-4F61-AFF9-6B43D8E9E401}");}

    /// <summary>Unregisters a class from the BuildMethods component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{16B2A5BC-9805-4F61-AFF9-6B43D8E9E401}");}
  }

  /// <summary>Registers or unregisters a class to the CadastralEditorPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CadastralEditorPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CadastralEditorPages : CatReg
  {

    /// <summary>Registers a class to the CadastralEditorPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DB89CF8D-FB81-4900-9BFE-37D83C376825}");}

    /// <summary>Unregisters a class from the CadastralEditorPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DB89CF8D-FB81-4900-9BFE-37D83C376825}");}
  }

  /// <summary>Registers or unregisters a class to the CadastralFabricPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CadastralFabricPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CadastralFabricPropertyPages : CatReg
  {

    /// <summary>Registers a class to the CadastralFabricPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6BC02511-2FFD-4D04-B98A-BB999D5A0062}");}

    /// <summary>Unregisters a class from the CadastralFabricPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6BC02511-2FFD-4D04-B98A-BB999D5A0062}");}
  }

  /// <summary>Registers or unregisters a class to the CadastralOptionPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CadastralOptionPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CadastralOptionPages : CatReg
  {

    /// <summary>Registers a class to the CadastralOptionPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8543A60D-BB09-453B-8636-7C05B0A90ABB}");}

    /// <summary>Unregisters a class from the CadastralOptionPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8543A60D-BB09-453B-8636-7C05B0A90ABB}");}
  }

  /// <summary>Registers or unregisters a class to the CadastralPlanPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CadastralPlanPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CadastralPlanPages : CatReg
  {

    /// <summary>Registers a class to the CadastralPlanPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0829B6F2-79A2-4CCC-BC50-7535634E065F}");}

    /// <summary>Unregisters a class from the CadastralPlanPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0829B6F2-79A2-4CCC-BC50-7535634E065F}");}
  }

  /// <summary>Registers or unregisters a class to the CadDrawingPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CadDrawingPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CadDrawingPropertyPages : CatReg
  {

    /// <summary>Registers a class to the CadDrawingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9C7-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the CadDrawingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9C7-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the CadFeatureClassPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CadFeatureClassPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CadFeatureClassPropertyPages : CatReg
  {

    /// <summary>Registers a class to the CadFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9C6-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the CadFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9C6-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the CadFeaturePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CadFeaturePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CadFeaturePropertyPages : CatReg
  {

    /// <summary>Registers a class to the CadFeaturePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9C5-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the CadFeaturePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9C5-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXBasemapLayerAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXBasemapLayerAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXBasemapLayerAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXBasemapLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{607EF61A-37AB-4FE3-A332-544355E5B8D4}");}

    /// <summary>Unregisters a class from the CartoXBasemapLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{607EF61A-37AB-4FE3-A332-544355E5B8D4}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXBasemapLayerMapAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXBasemapLayerMapAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXBasemapLayerMapAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXBasemapLayerMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0A49BC57-E700-4F8A-A143-54FDD9DC2C36}");}

    /// <summary>Unregisters a class from the CartoXBasemapLayerMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0A49BC57-E700-4F8A-A143-54FDD9DC2C36}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXMXDLayerAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXMXDLayerAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXMXDLayerAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXMXDLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E995934E-0ABF-4A7E-A1E6-198124C0589D}");}

    /// <summary>Unregisters a class from the CartoXMXDLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E995934E-0ABF-4A7E-A1E6-198124C0589D}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXMXDMapAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXMXDMapAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXMXDMapAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXMXDMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9B6D3B87-67BE-4E08-A295-E58E2114630A}");}

    /// <summary>Unregisters a class from the CartoXMXDMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9B6D3B87-67BE-4E08-A295-E58E2114630A}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXPackagerLayerAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXPackagerLayerAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXPackagerLayerAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXPackagerLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BD9C2D01-443C-4E7E-9AAC-9EC4BA1EA91C}");}

    /// <summary>Unregisters a class from the CartoXPackagerLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BD9C2D01-443C-4E7E-9AAC-9EC4BA1EA91C}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXPackagerMapAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXPackagerMapAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXPackagerMapAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXPackagerMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5A89BAF7-1DBC-4D21-BB7B-DB3E515212BC}");}

    /// <summary>Unregisters a class from the CartoXPackagerMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5A89BAF7-1DBC-4D21-BB7B-DB3E515212BC}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXPublishTargets component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXPublishTargets class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXPublishTargets : CatReg
  {

    /// <summary>Registers a class to the CartoXPublishTargets component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7BC19923-E346-4935-8891-D8911153F8AF}");}

    /// <summary>Unregisters a class from the CartoXPublishTargets component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7BC19923-E346-4935-8891-D8911153F8AF}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXSDSLayerAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXSDSLayerAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXSDSLayerAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXSDSLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7603A037-5E7F-49B0-ADDF-8A4256735CFD}");}

    /// <summary>Unregisters a class from the CartoXSDSLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7603A037-5E7F-49B0-ADDF-8A4256735CFD}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXSDSMapAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXSDSMapAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXSDSMapAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXSDSMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F2491DF4-D34F-4AEE-B11C-3C4F3BF1562E}");}

    /// <summary>Unregisters a class from the CartoXSDSMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F2491DF4-D34F-4AEE-B11C-3C4F3BF1562E}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXServerLayerAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXServerLayerAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXServerLayerAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXServerLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{346F6F5D-1B47-4678-8DF9-8E0172D85383}");}

    /// <summary>Unregisters a class from the CartoXServerLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{346F6F5D-1B47-4678-8DF9-8E0172D85383}");}
  }

  /// <summary>Registers or unregisters a class to the CartoXServerMapAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CartoXServerMapAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CartoXServerMapAnalyzers : CatReg
  {

    /// <summary>Registers a class to the CartoXServerMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DF5665C7-3368-45CD-B12E-7B317F458886}");}

    /// <summary>Unregisters a class from the CartoXServerMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DF5665C7-3368-45CD-B12E-7B317F458886}");}
  }

  /// <summary>Registers or unregisters a class to the CheckOutPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CheckOutPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CheckOutPropertyPages : CatReg
  {

    /// <summary>Registers a class to the CheckOutPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2FB78DC2-0E92-41F5-93ED-475CEACB2693}");}

    /// <summary>Unregisters a class from the CheckOutPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2FB78DC2-0E92-41F5-93ED-475CEACB2693}");}
  }

  /// <summary>Registers or unregisters a class to the ClassificationMethods component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ClassificationMethods class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ClassificationMethods : CatReg
  {

    /// <summary>Registers a class to the ClassificationMethods component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F5B68AD5-EB4E-11D1-AAB9-00C04FA334B3}");}

    /// <summary>Unregisters a class from the ClassificationMethods component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F5B68AD5-EB4E-11D1-AAB9-00C04FA334B3}");}
  }

  /// <summary>Registers or unregisters a class to the ClipboardFormats component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ClipboardFormats class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ClipboardFormats : CatReg
  {

    /// <summary>Registers a class to the ClipboardFormats component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{52BB5364-947E-11D2-ACFF-0000F87808EE}");}

    /// <summary>Unregisters a class from the ClipboardFormats component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{52BB5364-947E-11D2-ACFF-0000F87808EE}");}
  }

  /// <summary>Registers or unregisters a class to the ColorCorrectionPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ColorCorrectionPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ColorCorrectionPages : CatReg
  {

    /// <summary>Registers a class to the ColorCorrectionPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3745A6D7-50EF-11D3-9FF4-00C04F6BC8DD}");}

    /// <summary>Unregisters a class from the ColorCorrectionPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3745A6D7-50EF-11D3-9FF4-00C04F6BC8DD}");}
  }

  /// <summary>Registers or unregisters a class to the ColorPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ColorPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ColorPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ColorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{31CB4BD9-2FDC-11D3-9F58-00C04F6BC709}");}

    /// <summary>Unregisters a class from the ColorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{31CB4BD9-2FDC-11D3-9F58-00C04F6BC709}");}
  }

  /// <summary>Registers or unregisters a class to the ColorRamp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ColorRamp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ColorRamp : CatReg
  {

    /// <summary>Registers a class to the ColorRamp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2411EC71-8BCC-11D2-A2EE-080009B6F22B}");}

    /// <summary>Unregisters a class from the ColorRamp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2411EC71-8BCC-11D2-A2EE-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the ColorRampPropetyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ColorRampPropetyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ColorRampPropetyPages : CatReg
  {

    /// <summary>Registers a class to the ColorRampPropetyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2411EC72-8BCC-11D2-A2EE-080009B6F22B}");}

    /// <summary>Unregisters a class from the ColorRampPropetyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2411EC72-8BCC-11D2-A2EE-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the ContentsViews component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ContentsViews class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ContentsViews : CatReg
  {

    /// <summary>Registers a class to the ContentsViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{089874FC-CC18-11D2-9F39-00C04F6BC78E}");}

    /// <summary>Unregisters a class from the ContentsViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{089874FC-CC18-11D2-9F39-00C04F6BC78E}");}
  }

  /// <summary>Registers or unregisters a class to the ContentsWindowPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ContentsWindowPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ContentsWindowPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ContentsWindowPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{62125B17-5ADE-48F8-9041-1C18B0CAF56A}");}

    /// <summary>Unregisters a class from the ContentsWindowPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{62125B17-5ADE-48F8-9041-1C18B0CAF56A}");}
  }

  /// <summary>Registers or unregisters a class to the ContextAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ContextAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ContextAnalyzers : CatReg
  {

    /// <summary>Registers a class to the ContextAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0C452011-84CB-11D2-AE68-080009EC732A}");}

    /// <summary>Unregisters a class from the ContextAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0C452011-84CB-11D2-AE68-080009EC732A}");}
  }

  /// <summary>Registers or unregisters a class to the ControlsCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ControlsCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ControlsCommands : CatReg
  {

    /// <summary>Registers a class to the ControlsCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B284D891-22EE-4F12-A0A9-B1DDED9197F4}");}

    /// <summary>Unregisters a class from the ControlsCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B284D891-22EE-4F12-A0A9-B1DDED9197F4}");}
  }

  /// <summary>Registers or unregisters a class to the ControlsMenus component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ControlsMenus class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ControlsMenus : CatReg
  {

    /// <summary>Registers a class to the ControlsMenus component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B7D74382-06A8-483F-8FE5-6FB08FAA356A}");}

    /// <summary>Unregisters a class from the ControlsMenus component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B7D74382-06A8-483F-8FE5-6FB08FAA356A}");}
  }

  /// <summary>Registers or unregisters a class to the ControlsPalettes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ControlsPalettes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ControlsPalettes : CatReg
  {

    /// <summary>Registers a class to the ControlsPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F278DFAD-3B0B-4708-99BF-227B113CB10B}");}

    /// <summary>Unregisters a class from the ControlsPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F278DFAD-3B0B-4708-99BF-227B113CB10B}");}
  }

  /// <summary>Registers or unregisters a class to the ControlsToolbars component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ControlsToolbars class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ControlsToolbars : CatReg
  {

    /// <summary>Registers a class to the ControlsToolbars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5155BBC7-A6E9-4AF9-81DB-A16742D5A026}");}

    /// <summary>Unregisters a class from the ControlsToolbars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5155BBC7-A6E9-4AF9-81DB-A16742D5A026}");}
  }

  /// <summary>Registers or unregisters a class to the CoverageFeatureClassPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CoverageFeatureClassPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CoverageFeatureClassPropertyPages : CatReg
  {

    /// <summary>Registers a class to the CoverageFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5F7BBE84-E6EC-11D2-9F30-00C04F79927C}");}

    /// <summary>Unregisters a class from the CoverageFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5F7BBE84-E6EC-11D2-9F30-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the CoveragePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CoveragePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CoveragePropertyPages : CatReg
  {

    /// <summary>Registers a class to the CoveragePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5F7BBE83-E6EC-11D2-9F30-00C04F79927C}");}

    /// <summary>Unregisters a class from the CoveragePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5F7BBE83-E6EC-11D2-9F30-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the CustomCheckOutPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the CustomCheckOutPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class CustomCheckOutPropertyPages : CatReg
  {

    /// <summary>Registers a class to the CustomCheckOutPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{41F6E18F-F627-42F4-B5DA-E64A06D613C9}");}

    /// <summary>Unregisters a class from the CustomCheckOutPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{41F6E18F-F627-42F4-B5DA-E64A06D613C9}");}
  }

  /// <summary>Registers or unregisters a class to the DatabaseServerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DatabaseServerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DatabaseServerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the DatabaseServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3A53529A-F2C2-4015-A61B-F8760FD4429E}");}

    /// <summary>Unregisters a class from the DatabaseServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3A53529A-F2C2-4015-A61B-F8760FD4429E}");}
  }

  /// <summary>Registers or unregisters a class to the DataExclusionPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DataExclusionPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DataExclusionPropertyPages : CatReg
  {

    /// <summary>Registers a class to the DataExclusionPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{75C2A63E-A98A-11D2-AB27-00C04FA334B3}");}

    /// <summary>Unregisters a class from the DataExclusionPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{75C2A63E-A98A-11D2-AB27-00C04FA334B3}");}
  }

  /// <summary>Registers or unregisters a class to the DataGraphPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DataGraphPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DataGraphPropertyPages : CatReg
  {

    /// <summary>Registers a class to the DataGraphPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{977D75CF-E00C-11D3-A664-0008C7DF88DB}");}

    /// <summary>Unregisters a class from the DataGraphPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{977D75CF-E00C-11D3-A664-0008C7DF88DB}");}
  }

  /// <summary>Registers or unregisters a class to the DataSamplingPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DataSamplingPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DataSamplingPropertyPages : CatReg
  {

    /// <summary>Registers a class to the DataSamplingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5C15FD91-2DB2-11D3-9F52-00C04F6BC709}");}

    /// <summary>Unregisters a class from the DataSamplingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5C15FD91-2DB2-11D3-9F52-00C04F6BC709}");}
  }

  /// <summary>Registers or unregisters a class to the DataWindowFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DataWindowFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DataWindowFactory : CatReg
  {

    /// <summary>Registers a class to the DataWindowFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B56A7C49-83D4-11D2-A2E9-080009B6F22B}");}

    /// <summary>Unregisters a class from the DataWindowFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B56A7C49-83D4-11D2-A2E9-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the DDDAnalystOptionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DDDAnalystOptionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDDAnalystOptionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the DDDAnalystOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FA38E30A-906F-4B90-94B5-68B8E33181EC}");}

    /// <summary>Unregisters a class from the DDDAnalystOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FA38E30A-906F-4B90-94B5-68B8E33181EC}");}
  }

  /// <summary>Registers or unregisters a class to the DDDAnimationTypes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DDDAnimationTypes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DDDAnimationTypes : CatReg
  {

    /// <summary>Registers a class to the DDDAnimationTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5980E69C-A95E-11D5-B2A0-00508BCDDE28}");}

    /// <summary>Unregisters a class from the DDDAnimationTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5980E69C-A95E-11D5-B2A0-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the DimensionConstructors component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DimensionConstructors class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DimensionConstructors : CatReg
  {

    /// <summary>Registers a class to the DimensionConstructors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0864F69B-E975-11D3-9F79-00C04F6BDDD9}");}

    /// <summary>Unregisters a class from the DimensionConstructors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0864F69B-E975-11D3-9F79-00C04F6BDDD9}");}
  }

  /// <summary>Registers or unregisters a class to the DynamicText component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the DynamicText class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class DynamicText : CatReg
  {

    /// <summary>Registers a class to the DynamicText component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9297C9A7-B79A-4D9B-B737-E463A5D15F06}");}

    /// <summary>Unregisters a class from the DynamicText component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9297C9A7-B79A-4D9B-B737-E463A5D15F06}");}
  }

  /// <summary>Registers or unregisters a class to the EditorExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EditorExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EditorExtensions : CatReg
  {

    /// <summary>Registers a class to the EditorExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{58122E51-D89C-11D2-9F25-00C04F6BC979}");}

    /// <summary>Unregisters a class from the EditorExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{58122E51-D89C-11D2-9F25-00C04F6BC979}");}
  }

  /// <summary>Registers or unregisters a class to the EditorPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EditorPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EditorPropertyPages : CatReg
  {

    /// <summary>Registers a class to the EditorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{58122E52-D89C-11D2-9F25-00C04F6BC979}");}

    /// <summary>Unregisters a class from the EditorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{58122E52-D89C-11D2-9F25-00C04F6BC979}");}
  }

  /// <summary>Registers or unregisters a class to the EditorToolbars component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EditorToolbars class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EditorToolbars : CatReg
  {

    /// <summary>Registers a class to the EditorToolbars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0DA7AF0F-EA0F-4EC8-96EA-96642C8C7524}");}

    /// <summary>Unregisters a class from the EditorToolbars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0DA7AF0F-EA0F-4EC8-96EA-96642C8C7524}");}
  }

  /// <summary>Registers or unregisters a class to the EditTasks component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EditTasks class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EditTasks : CatReg
  {

    /// <summary>Registers a class to the EditTasks component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{58122E50-D89C-11D2-9F25-00C04F6BC979}");}

    /// <summary>Unregisters a class from the EditTasks component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{58122E50-D89C-11D2-9F25-00C04F6BC979}");}
  }

  /// <summary>Registers or unregisters a class to the EditTemplatePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EditTemplatePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EditTemplatePropertyPages : CatReg
  {

    /// <summary>Registers a class to the EditTemplatePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B6C88DB3-9E9E-4F5C-B5E7-7E76B2ADAA54}");}

    /// <summary>Unregisters a class from the EditTemplatePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B6C88DB3-9E9E-4F5C-B5E7-7E76B2ADAA54}");}
  }

  /// <summary>Registers or unregisters a class to the EditToolMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EditToolMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EditToolMenuCommands : CatReg
  {

    /// <summary>Registers a class to the EditToolMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E98F1115-EFA4-41D7-9982-F733FF42BA0B}");}

    /// <summary>Unregisters a class from the EditToolMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E98F1115-EFA4-41D7-9982-F733FF42BA0B}");}
  }

  /// <summary>Registers or unregisters a class to the ElementPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ElementPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ElementPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ElementPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{43B21395-F1E2-11D2-B870-00600802E603}");}

    /// <summary>Unregisters a class from the ElementPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{43B21395-F1E2-11D2-B870-00600802E603}");}
  }

  /// <summary>Registers or unregisters a class to the EndpointCoveredByPointErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EndpointCoveredByPointErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EndpointCoveredByPointErrorCommands : CatReg
  {

    /// <summary>Registers a class to the EndpointCoveredByPointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{22CB4C7D-0ED3-4BE1-9A56-1B1D65EA0B50}");}

    /// <summary>Unregisters a class from the EndpointCoveredByPointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{22CB4C7D-0ED3-4BE1-9A56-1B1D65EA0B50}");}
  }

  /// <summary>Registers or unregisters a class to the EngineDataDialogBrowser component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EngineDataDialogBrowser class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EngineDataDialogBrowser : CatReg
  {

    /// <summary>Registers a class to the EngineDataDialogBrowser component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{14C731E1-AAB5-4502-AD7D-08B6C963C997}");}

    /// <summary>Unregisters a class from the EngineDataDialogBrowser component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{14C731E1-AAB5-4502-AD7D-08B6C963C997}");}
  }

  /// <summary>Registers or unregisters a class to the EngineEditTasks component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EngineEditTasks class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EngineEditTasks : CatReg
  {

    /// <summary>Registers a class to the EngineEditTasks component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{03B065EF-FA91-4B06-9E03-D5F40EF605E1}");}

    /// <summary>Unregisters a class from the EngineEditTasks component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{03B065EF-FA91-4B06-9E03-D5F40EF605E1}");}
  }

  /// <summary>Registers or unregisters a class to the EngineExtension component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EngineExtension class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EngineExtension : CatReg
  {

    /// <summary>Registers a class to the EngineExtension component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{12E95019-C871-4853-B4FF-EA37847ABAA6}");}

    /// <summary>Unregisters a class from the EngineExtension component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{12E95019-C871-4853-B4FF-EA37847ABAA6}");}
  }

  /// <summary>Registers or unregisters a class to the EngineExtensionJIT component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EngineExtensionJIT class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EngineExtensionJIT : CatReg
  {

    /// <summary>Registers a class to the EngineExtensionJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F17FC8EF-9576-45FA-ADA2-D80E2BA7DE1C}");}

    /// <summary>Unregisters a class from the EngineExtensionJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F17FC8EF-9576-45FA-ADA2-D80E2BA7DE1C}");}
  }

  /// <summary>Registers or unregisters a class to the EngineNetworkAnalystWindowItemCategory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EngineNetworkAnalystWindowItemCategory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EngineNetworkAnalystWindowItemCategory : CatReg
  {

    /// <summary>Registers a class to the EngineNetworkAnalystWindowItemCategory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E194B8CD-E477-4A81-BDC7-8FCA8E4C62A1}");}

    /// <summary>Unregisters a class from the EngineNetworkAnalystWindowItemCategory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E194B8CD-E477-4A81-BDC7-8FCA8E4C62A1}");}
  }

  /// <summary>Registers or unregisters a class to the EngineRoutingServiceCategory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EngineRoutingServiceCategory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EngineRoutingServiceCategory : CatReg
  {

    /// <summary>Registers a class to the EngineRoutingServiceCategory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B4981936-C398-4354-B857-CB8AB4BF67FE}");}

    /// <summary>Unregisters a class from the EngineRoutingServiceCategory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B4981936-C398-4354-B857-CB8AB4BF67FE}");}
  }

  /// <summary>Registers or unregisters a class to the EngineSchematicCreateDiagramDialog component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EngineSchematicCreateDiagramDialog class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EngineSchematicCreateDiagramDialog : CatReg
  {

    /// <summary>Registers a class to the EngineSchematicCreateDiagramDialog component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E6036C13-5FD0-4AAD-963E-BCF61E6CD646}");}

    /// <summary>Unregisters a class from the EngineSchematicCreateDiagramDialog component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E6036C13-5FD0-4AAD-963E-BCF61E6CD646}");}
  }

  /// <summary>Registers or unregisters a class to the EngineSnapAgents component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the EngineSnapAgents class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class EngineSnapAgents : CatReg
  {

    /// <summary>Registers a class to the EngineSnapAgents component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{85382FF5-7283-4276-A467-5A75308D0C65}");}

    /// <summary>Unregisters a class from the EngineSnapAgents component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{85382FF5-7283-4276-A467-5A75308D0C65}");}
  }

  /// <summary>Registers or unregisters a class to the ESDAEngineMethods component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ESDAEngineMethods class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ESDAEngineMethods : CatReg
  {

    /// <summary>Registers a class to the ESDAEngineMethods component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DA805B10-54D7-11D3-8D39-00C04F5B87B2}");}

    /// <summary>Unregisters a class from the ESDAEngineMethods component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DA805B10-54D7-11D3-8D39-00C04F5B87B2}");}
  }

  /// <summary>Registers or unregisters a class to the ESRIDeveloperKitLibraryHandlingExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ESRIDeveloperKitLibraryHandlingExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ESRIDeveloperKitLibraryHandlingExtensions : CatReg
  {

    /// <summary>Registers a class to the ESRIDeveloperKitLibraryHandlingExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D25CC5EB-97E5-456C-88D2-66849B9C42CE}");}

    /// <summary>Unregisters a class from the ESRIDeveloperKitLibraryHandlingExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D25CC5EB-97E5-456C-88D2-66849B9C42CE}");}
  }

  /// <summary>Registers or unregisters a class to the ESRIExportPropertyDialogs component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ESRIExportPropertyDialogs class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ESRIExportPropertyDialogs : CatReg
  {

    /// <summary>Registers a class to the ESRIExportPropertyDialogs component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AE54680B-8099-4A93-8C29-6D727FBCF11A}");}

    /// <summary>Unregisters a class from the ESRIExportPropertyDialogs component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AE54680B-8099-4A93-8C29-6D727FBCF11A}");}
  }

  /// <summary>Registers or unregisters a class to the ESRIExportPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ESRIExportPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ESRIExportPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ESRIExportPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{93755985-E8DC-403A-BE30-B59A32193142}");}

    /// <summary>Unregisters a class from the ESRIExportPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{93755985-E8DC-403A-BE30-B59A32193142}");}
  }

  /// <summary>Registers or unregisters a class to the ESRIPrintEnginePropertyDialogs component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ESRIPrintEnginePropertyDialogs class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ESRIPrintEnginePropertyDialogs : CatReg
  {

    /// <summary>Registers a class to the ESRIPrintEnginePropertyDialogs component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{62CB8B33-AB40-4C3F-B3EE-A56EBF044D38}");}

    /// <summary>Unregisters a class from the ESRIPrintEnginePropertyDialogs component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{62CB8B33-AB40-4C3F-B3EE-A56EBF044D38}");}
  }

  /// <summary>Registers or unregisters a class to the ESRIRasterPrintDrivers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ESRIRasterPrintDrivers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ESRIRasterPrintDrivers : CatReg
  {

    /// <summary>Registers a class to the ESRIRasterPrintDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CB4F289F-4FA6-4B70-8F57-807C5A60308C}");}

    /// <summary>Unregisters a class from the ESRIRasterPrintDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CB4F289F-4FA6-4B70-8F57-807C5A60308C}");}
  }

  /// <summary>Registers or unregisters a class to the ESRIRasterPrintDriversPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ESRIRasterPrintDriversPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ESRIRasterPrintDriversPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ESRIRasterPrintDriversPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{32079A2B-1A63-4A0F-A6D8-B5164D1BE269}");}

    /// <summary>Unregisters a class from the ESRIRasterPrintDriversPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{32079A2B-1A63-4A0F-A6D8-B5164D1BE269}");}
  }

  /// <summary>Registers or unregisters a class to the ExporterDrivers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ExporterDrivers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ExporterDrivers : CatReg
  {

    /// <summary>Registers a class to the ExporterDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5FDE0991-7B12-11D2-ACF9-0000F87808EE}");}

    /// <summary>Unregisters a class from the ExporterDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5FDE0991-7B12-11D2-ACF9-0000F87808EE}");}
  }

  /// <summary>Registers or unregisters a class to the ExporterPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ExporterPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ExporterPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ExporterPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5FDE099A-7B12-11D2-ACF9-0000F87808EE}");}

    /// <summary>Unregisters a class from the ExporterPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5FDE099A-7B12-11D2-ACF9-0000F87808EE}");}
  }

  /// <summary>Registers or unregisters a class to the Exports component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the Exports class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class Exports : CatReg
  {

    /// <summary>Registers a class to the Exports component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{66A7ECF7-9BE1-4E77-A8C7-42D3C62A2590}");}

    /// <summary>Unregisters a class from the Exports component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{66A7ECF7-9BE1-4E77-A8C7-42D3C62A2590}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureClassPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureClassPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureClassPropertyPages : CatReg
  {

    /// <summary>Registers a class to the FeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{750D818E-E0B5-11D2-99BF-0000F80372B4}");}

    /// <summary>Unregisters a class from the FeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{750D818E-E0B5-11D2-99BF-0000F80372B4}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionAnnotationTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionAnnotationTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionAnnotationTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionAnnotationTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1ADBF249-5F5C-4559-AD0D-A66126F4F260}");}

    /// <summary>Unregisters a class from the FeatureConstructionAnnotationTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1ADBF249-5F5C-4559-AD0D-A66126F4F260}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionCOGOLineTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionCOGOLineTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionCOGOLineTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionCOGOLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DD3E22F8-54D1-45A4-B4B5-FD50707111EE}");}

    /// <summary>Unregisters a class from the FeatureConstructionCOGOLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DD3E22F8-54D1-45A4-B4B5-FD50707111EE}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionDimensionTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionDimensionTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionDimensionTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionDimensionTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{12390BFF-231F-4DAC-B691-844D86357BFE}");}

    /// <summary>Unregisters a class from the FeatureConstructionDimensionTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{12390BFF-231F-4DAC-B691-844D86357BFE}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionGNLineTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionGNLineTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionGNLineTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionGNLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{63F44075-F9F0-4C70-8E5D-7B939A82478A}");}

    /// <summary>Unregisters a class from the FeatureConstructionGNLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{63F44075-F9F0-4C70-8E5D-7B939A82478A}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionMultipatchTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionMultipatchTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionMultipatchTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionMultipatchTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F9B5A652-7B95-4043-93A0-33FC98935D06}");}

    /// <summary>Unregisters a class from the FeatureConstructionMultipatchTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F9B5A652-7B95-4043-93A0-33FC98935D06}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionMultipointTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionMultipointTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionMultipointTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionMultipointTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9ABA92EC-D553-4EF6-BF6C-152275687DFC}");}

    /// <summary>Unregisters a class from the FeatureConstructionMultipointTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9ABA92EC-D553-4EF6-BF6C-152275687DFC}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionPointTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionPointTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionPointTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionPointTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{64BB9AD9-E01F-46DD-BED3-0FC7FFEFE28C}");}

    /// <summary>Unregisters a class from the FeatureConstructionPointTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{64BB9AD9-E01F-46DD-BED3-0FC7FFEFE28C}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionPolygonTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionPolygonTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionPolygonTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionPolygonTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D0567AD9-3F8D-4C51-8DEF-4321DB00C15C}");}

    /// <summary>Unregisters a class from the FeatureConstructionPolygonTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D0567AD9-3F8D-4C51-8DEF-4321DB00C15C}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionPolylineTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionPolylineTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionPolylineTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionPolylineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2B615FA0-67AF-4F17-8E59-CE26152E7B96}");}

    /// <summary>Unregisters a class from the FeatureConstructionPolylineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2B615FA0-67AF-4F17-8E59-CE26152E7B96}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureConstructionTurnLineTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureConstructionTurnLineTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureConstructionTurnLineTools : CatReg
  {

    /// <summary>Registers a class to the FeatureConstructionTurnLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6F0DF607-1AE3-4947-94A1-996CCA4A5E2A}");}

    /// <summary>Unregisters a class from the FeatureConstructionTurnLineTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6F0DF607-1AE3-4947-94A1-996CCA4A5E2A}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureDatasetPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureDatasetPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureDatasetPropertyPages : CatReg
  {

    /// <summary>Registers a class to the FeatureDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6EDC31E1-E3AD-11D2-99C1-0000F80372B4}");}

    /// <summary>Unregisters a class from the FeatureDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6EDC31E1-E3AD-11D2-99C1-0000F80372B4}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureLargerThanToleranceErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureLargerThanToleranceErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureLargerThanToleranceErrorCommands : CatReg
  {

    /// <summary>Registers a class to the FeatureLargerThanToleranceErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C7567B1B-A072-4FFC-AD9C-A1C9F66DC54D}");}

    /// <summary>Unregisters a class from the FeatureLargerThanToleranceErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C7567B1B-A072-4FFC-AD9C-A1C9F66DC54D}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureLayerSymbology component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureLayerSymbology class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureLayerSymbology : CatReg
  {

    /// <summary>Registers a class to the FeatureLayerSymbology component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7480BE41-EEA1-4E16-858C-B2AB6C92F720}");}

    /// <summary>Unregisters a class from the FeatureLayerSymbology component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7480BE41-EEA1-4E16-858C-B2AB6C92F720}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureServiceLayerAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureServiceLayerAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureServiceLayerAnalyzers : CatReg
  {

    /// <summary>Registers a class to the FeatureServiceLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B1AAFF8B-5F6E-49B6-B237-CF8DC8A41622}");}

    /// <summary>Unregisters a class from the FeatureServiceLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B1AAFF8B-5F6E-49B6-B237-CF8DC8A41622}");}
  }

  /// <summary>Registers or unregisters a class to the FeatureServiceMapAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FeatureServiceMapAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FeatureServiceMapAnalyzers : CatReg
  {

    /// <summary>Registers a class to the FeatureServiceMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8509D064-065A-4825-B27C-9241193643BA}");}

    /// <summary>Unregisters a class from the FeatureServiceMapAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8509D064-065A-4825-B27C-9241193643BA}");}
  }

  /// <summary>Registers or unregisters a class to the FillSymbol component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FillSymbol class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FillSymbol : CatReg
  {

    /// <summary>Registers a class to the FillSymbol component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5424FB02-5713-11D2-97E5-0080C7E04196}");}

    /// <summary>Unregisters a class from the FillSymbol component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5424FB02-5713-11D2-97E5-0080C7E04196}");}
  }

  /// <summary>Registers or unregisters a class to the FontMappingPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FontMappingPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FontMappingPropertyPages : CatReg
  {

    /// <summary>Registers a class to the FontMappingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FB5216EF-6AC6-11D3-9F4E-00C04F6BC8DD}");}

    /// <summary>Unregisters a class from the FontMappingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FB5216EF-6AC6-11D3-9F4E-00C04F6BC8DD}");}
  }

  /// <summary>Registers or unregisters a class to the FrameElementPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the FrameElementPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class FrameElementPropertyPages : CatReg
  {

    /// <summary>Registers a class to the FrameElementPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{43B21396-F1E2-11D2-B870-00600802E603}");}

    /// <summary>Unregisters a class from the FrameElementPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{43B21396-F1E2-11D2-B870-00600802E603}");}
  }

  /// <summary>Registers or unregisters a class to the GARenderersPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GARenderersPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GARenderersPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GARenderersPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{22FA66AB-1522-4463-A230-89BFC071C16F}");}

    /// <summary>Unregisters a class from the GARenderersPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{22FA66AB-1522-4463-A230-89BFC071C16F}");}
  }

  /// <summary>Registers or unregisters a class to the GeoAnalysis component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeoAnalysis class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeoAnalysis : CatReg
  {

    /// <summary>Registers a class to the GeoAnalysis component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3297E9C1-93A1-11D2-9F33-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the GeoAnalysis component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3297E9C1-93A1-11D2-9F33-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the GeodatabaseDistributedPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeodatabaseDistributedPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeodatabaseDistributedPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GeodatabaseDistributedPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{235D92EF-9009-424C-A668-464157D3C9EE}");}

    /// <summary>Unregisters a class from the GeodatabaseDistributedPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{235D92EF-9009-424C-A668-464157D3C9EE}");}
  }

  /// <summary>Registers or unregisters a class to the GeodatabaseWorkspaceExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeodatabaseWorkspaceExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeodatabaseWorkspaceExtensions : CatReg
  {

    /// <summary>Registers a class to the GeodatabaseWorkspaceExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DA10C1C7-09A3-11D4-9FAA-00C04F6BDF0C}");}

    /// <summary>Unregisters a class from the GeodatabaseWorkspaceExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DA10C1C7-09A3-11D4-9FAA-00C04F6BDF0C}");}
  }

  /// <summary>Registers or unregisters a class to the GeoDataServerDatasetAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeoDataServerDatasetAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeoDataServerDatasetAnalyzers : CatReg
  {

    /// <summary>Registers a class to the GeoDataServerDatasetAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{706B874A-7CA6-47CA-8C2B-6A3059917BB2}");}

    /// <summary>Unregisters a class from the GeoDataServerDatasetAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{706B874A-7CA6-47CA-8C2B-6A3059917BB2}");}
  }

  /// <summary>Registers or unregisters a class to the GeoDataServerWorkspaceAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeoDataServerWorkspaceAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeoDataServerWorkspaceAnalyzers : CatReg
  {

    /// <summary>Registers a class to the GeoDataServerWorkspaceAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D4AAEC8E-56F6-4E62-AF9D-4680FBE90F25}");}

    /// <summary>Unregisters a class from the GeoDataServerWorkspaceAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D4AAEC8E-56F6-4E62-AF9D-4680FBE90F25}");}
  }

  /// <summary>Registers or unregisters a class to the GeoElementTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeoElementTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeoElementTools : CatReg
  {

    /// <summary>Registers a class to the GeoElementTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B56A7C44-83D4-11D2-A2E9-080009B6F22B}");}

    /// <summary>Unregisters a class from the GeoElementTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B56A7C44-83D4-11D2-A2E9-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the GeographicCoordSysPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeographicCoordSysPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeographicCoordSysPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GeographicCoordSysPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7E9913E1-E22E-11D2-99C0-0000F80372B4}");}

    /// <summary>Unregisters a class from the GeographicCoordSysPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7E9913E1-E22E-11D2-99C0-0000F80372B4}");}
  }

  /// <summary>Registers or unregisters a class to the GeometricEffect component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeometricEffect class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeometricEffect : CatReg
  {

    /// <summary>Registers a class to the GeometricEffect component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{72E05255-883F-441A-B29B-48FE55CF6A61}");}

    /// <summary>Unregisters a class from the GeometricEffect component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{72E05255-883F-441A-B29B-48FE55CF6A61}");}
  }

  /// <summary>Registers or unregisters a class to the GeometricNetworkPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeometricNetworkPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeometricNetworkPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GeometricNetworkPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{750D818F-E0B5-11D2-99BF-0000F80372B4}");}

    /// <summary>Unregisters a class from the GeometricNetworkPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{750D818F-E0B5-11D2-99BF-0000F80372B4}");}
  }

  /// <summary>Registers or unregisters a class to the GeoObjectClassDescriptions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeoObjectClassDescriptions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeoObjectClassDescriptions : CatReg
  {

    /// <summary>Registers a class to the GeoObjectClassDescriptions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0813623A-A72E-11D2-8924-0000F877762D}");}

    /// <summary>Unregisters a class from the GeoObjectClassDescriptions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0813623A-A72E-11D2-8924-0000F877762D}");}
  }

  /// <summary>Registers or unregisters a class to the GeoObjectClassExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeoObjectClassExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeoObjectClassExtensions : CatReg
  {

    /// <summary>Registers a class to the GeoObjectClassExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D4E2A322-5D59-11D2-89FD-006097AFF44E}");}

    /// <summary>Unregisters a class from the GeoObjectClassExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D4E2A322-5D59-11D2-89FD-006097AFF44E}");}
  }

  /// <summary>Registers or unregisters a class to the GeoObjects component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeoObjects class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeoObjects : CatReg
  {

    /// <summary>Registers a class to the GeoObjects component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D4E2A321-5D59-11D2-89FD-006097AFF44E}");}

    /// <summary>Unregisters a class from the GeoObjects component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D4E2A321-5D59-11D2-89FD-006097AFF44E}");}
  }

  /// <summary>Registers or unregisters a class to the GeoRefSaveAsDlg component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GeoRefSaveAsDlg class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GeoRefSaveAsDlg : CatReg
  {

    /// <summary>Registers a class to the GeoRefSaveAsDlg component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9FB18846-5930-4D7A-AFBE-0FF2E4B6DA8C}");}

    /// <summary>Unregisters a class from the GeoRefSaveAsDlg component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9FB18846-5930-4D7A-AFBE-0FF2E4B6DA8C}");}
  }

  /// <summary>Registers or unregisters a class to the GISServersCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GISServersCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GISServersCommands : CatReg
  {

    /// <summary>Registers a class to the GISServersCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4EC5CC19-FA65-49D1-A953-A67BE066C467}");}

    /// <summary>Unregisters a class from the GISServersCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4EC5CC19-FA65-49D1-A953-A67BE066C467}");}
  }

  /// <summary>Registers or unregisters a class to the GlobeAnimationTypes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GlobeAnimationTypes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GlobeAnimationTypes : CatReg
  {

    /// <summary>Registers a class to the GlobeAnimationTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{350DE633-42A4-458D-B07B-35D3B10E12B6}");}

    /// <summary>Unregisters a class from the GlobeAnimationTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{350DE633-42A4-458D-B07B-35D3B10E12B6}");}
  }

  /// <summary>Registers or unregisters a class to the GlobePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GlobePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GlobePropertyPages : CatReg
  {

    /// <summary>Registers a class to the GlobePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21DA-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GlobePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21DA-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GlobeServerGlobeAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GlobeServerGlobeAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GlobeServerGlobeAnalyzers : CatReg
  {

    /// <summary>Registers a class to the GlobeServerGlobeAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{349B3F4B-C47F-4D19-A1E1-DBB3B42B3A3C}");}

    /// <summary>Unregisters a class from the GlobeServerGlobeAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{349B3F4B-C47F-4D19-A1E1-DBB3B42B3A3C}");}
  }

  /// <summary>Registers or unregisters a class to the GlobeServerLayerAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GlobeServerLayerAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GlobeServerLayerAnalyzers : CatReg
  {

    /// <summary>Registers a class to the GlobeServerLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FDE95218-0185-4EF2-8A38-A67E23A327DB}");}

    /// <summary>Unregisters a class from the GlobeServerLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FDE95218-0185-4EF2-8A38-A67E23A327DB}");}
  }

  /// <summary>Registers or unregisters a class to the GMxBaseLayerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxBaseLayerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxBaseLayerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GMxBaseLayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FD472D9C-43DB-4C67-B56E-A590CE7B47DC}");}

    /// <summary>Unregisters a class from the GMxBaseLayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FD472D9C-43DB-4C67-B56E-A590CE7B47DC}");}
  }

  /// <summary>Registers or unregisters a class to the GMxCommandBars component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxCommandBars class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxCommandBars : CatReg
  {

    /// <summary>Registers a class to the GMxCommandBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21D3-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxCommandBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21D3-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxCommands : CatReg
  {

    /// <summary>Registers a class to the GMxCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21D4-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21D4-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxContentsViews component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxContentsViews class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxContentsViews : CatReg
  {

    /// <summary>Registers a class to the GMxContentsViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21D7-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxContentsViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21D7-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxContextAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxContextAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxContextAnalyzers : CatReg
  {

    /// <summary>Registers a class to the GMxContextAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21D9-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxContextAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21D9-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxDockableWindows component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxDockableWindows class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxDockableWindows : CatReg
  {

    /// <summary>Registers a class to the GMxDockableWindows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21D8-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxDockableWindows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21D8-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxExtensions : CatReg
  {

    /// <summary>Registers a class to the GMxExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21D6-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21D6-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxExtensionsJIT component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxExtensionsJIT class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxExtensionsJIT : CatReg
  {

    /// <summary>Registers a class to the GMxExtensionsJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{99A23410-D290-41C8-83D8-123D37A1B67B}");}

    /// <summary>Unregisters a class from the GMxExtensionsJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{99A23410-D290-41C8-83D8-123D37A1B67B}");}
  }

  /// <summary>Registers or unregisters a class to the GMxFinders component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxFinders class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxFinders : CatReg
  {

    /// <summary>Registers a class to the GMxFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21DD-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21DD-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxLayerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxLayerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxLayerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GMxLayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21DB-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxLayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21DB-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxOptionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxOptionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxOptionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GMxOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21DE-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21DE-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxPalettes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxPalettes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxPalettes : CatReg
  {

    /// <summary>Registers a class to the GMxPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21D2-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21D2-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GMxPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GMxPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GMxPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GMxPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21DC-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GMxPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21DC-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GNEditorPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GNEditorPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GNEditorPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GNEditorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{583A720C-FC86-46A1-A6DD-E5C315076BEB}");}

    /// <summary>Unregisters a class from the GNEditorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{583A720C-FC86-46A1-A6DD-E5C315076BEB}");}
  }

  /// <summary>Registers or unregisters a class to the GPDataTypeFactories component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPDataTypeFactories class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPDataTypeFactories : CatReg
  {

    /// <summary>Registers a class to the GPDataTypeFactories component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CDA62C78-1221-4246-A622-61C354091657}");}

    /// <summary>Unregisters a class from the GPDataTypeFactories component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CDA62C78-1221-4246-A622-61C354091657}");}
  }

  /// <summary>Registers or unregisters a class to the GPFileTypes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPFileTypes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPFileTypes : CatReg
  {

    /// <summary>Registers a class to the GPFileTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B843DF6C-00FA-4BCB-B4E2-1BF6A0270C59}");}

    /// <summary>Unregisters a class from the GPFileTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B843DF6C-00FA-4BCB-B4E2-1BF6A0270C59}");}
  }

  /// <summary>Registers or unregisters a class to the GPFunctionFactories component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPFunctionFactories class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPFunctionFactories : CatReg
  {

    /// <summary>Registers a class to the GPFunctionFactories component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FD939A4A-955D-4094-B440-77083E410F41}");}

    /// <summary>Unregisters a class from the GPFunctionFactories component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FD939A4A-955D-4094-B440-77083E410F41}");}
  }

  /// <summary>Registers or unregisters a class to the GPFunctionFactoriesPrivate component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPFunctionFactoriesPrivate class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPFunctionFactoriesPrivate : CatReg
  {

    /// <summary>Registers a class to the GPFunctionFactoriesPrivate component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6E264847-6AAF-4050-8CC9-16B0CDDD620D}");}

    /// <summary>Unregisters a class from the GPFunctionFactoriesPrivate component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6E264847-6AAF-4050-8CC9-16B0CDDD620D}");}
  }

  /// <summary>Registers or unregisters a class to the GPPackagerTaskAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPPackagerTaskAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPPackagerTaskAnalyzers : CatReg
  {

    /// <summary>Registers a class to the GPPackagerTaskAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B441479D-4FE1-42FB-ABF1-DB4ACCE2EAA5}");}

    /// <summary>Unregisters a class from the GPPackagerTaskAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B441479D-4FE1-42FB-ABF1-DB4ACCE2EAA5}");}
  }

  /// <summary>Registers or unregisters a class to the GPPackagerToolAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPPackagerToolAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPPackagerToolAnalyzers : CatReg
  {

    /// <summary>Registers a class to the GPPackagerToolAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{26E079CD-6FB7-40D3-94F7-ED5438E072C5}");}

    /// <summary>Unregisters a class from the GPPackagerToolAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{26E079CD-6FB7-40D3-94F7-ED5438E072C5}");}
  }

  /// <summary>Registers or unregisters a class to the GPRuntimePackagerToolAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPRuntimePackagerToolAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPRuntimePackagerToolAnalyzers : CatReg
  {

    /// <summary>Registers a class to the GPRuntimePackagerToolAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C9B5C3F7-084E-44A5-95B5-35E5826117B1}");}

    /// <summary>Unregisters a class from the GPRuntimePackagerToolAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C9B5C3F7-084E-44A5-95B5-35E5826117B1}");}
  }

  /// <summary>Registers or unregisters a class to the GPToolboxMetadataPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPToolboxMetadataPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPToolboxMetadataPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GPToolboxMetadataPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AB874504-AF04-4138-9372-54311F8A3064}");}

    /// <summary>Unregisters a class from the GPToolboxMetadataPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AB874504-AF04-4138-9372-54311F8A3064}");}
  }

  /// <summary>Registers or unregisters a class to the GPToolboxPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPToolboxPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPToolboxPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GPToolboxPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F11ED154-DAB2-4B5C-9C31-AD1CDC06A20C}");}

    /// <summary>Unregisters a class from the GPToolboxPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F11ED154-DAB2-4B5C-9C31-AD1CDC06A20C}");}
  }

  /// <summary>Registers or unregisters a class to the GPToolExtensionFactories component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPToolExtensionFactories class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPToolExtensionFactories : CatReg
  {

    /// <summary>Registers a class to the GPToolExtensionFactories component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{02079C92-481B-4C37-8CD6-F530109D6016}");}

    /// <summary>Unregisters a class from the GPToolExtensionFactories component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{02079C92-481B-4C37-8CD6-F530109D6016}");}
  }

  /// <summary>Registers or unregisters a class to the GPToolMetadataPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPToolMetadataPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPToolMetadataPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GPToolMetadataPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B3612488-785F-4784-B967-D6EE34B72EAF}");}

    /// <summary>Unregisters a class from the GPToolMetadataPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B3612488-785F-4784-B967-D6EE34B72EAF}");}
  }

  /// <summary>Registers or unregisters a class to the GPToolPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GPToolPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GPToolPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GPToolPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{49F484F5-C1D5-4D89-B586-D23B5DF54E03}");}

    /// <summary>Unregisters a class from the GPToolPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{49F484F5-C1D5-4D89-B586-D23B5DF54E03}");}
  }

  /// <summary>Registers or unregisters a class to the GraphicSnapAgents component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GraphicSnapAgents class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GraphicSnapAgents : CatReg
  {

    /// <summary>Registers a class to the GraphicSnapAgents component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D618307B-AA29-11D2-87F2-0000F8751720}");}

    /// <summary>Unregisters a class from the GraphicSnapAgents component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D618307B-AA29-11D2-87F2-0000F8751720}");}
  }

  /// <summary>Registers or unregisters a class to the GridLabels component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GridLabels class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GridLabels : CatReg
  {

    /// <summary>Registers a class to the GridLabels component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8AF09A6C-A0DD-11D2-AE7F-080009EC732A}");}

    /// <summary>Unregisters a class from the GridLabels component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8AF09A6C-A0DD-11D2-AE7F-080009EC732A}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSAGOMapContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSAGOMapContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSAGOMapContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSAGOMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6DC1B675-62EC-41D8-8F3B-9D35B4979D37}");}

    /// <summary>Unregisters a class from the GxAGSAGOMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6DC1B675-62EC-41D8-8F3B-9D35B4979D37}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSCachingContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSCachingContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSCachingContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSCachingContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FEACA3A3-0212-4CF5-B1F5-F6393A15728C}");}

    /// <summary>Unregisters a class from the GxAGSCachingContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FEACA3A3-0212-4CF5-B1F5-F6393A15728C}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSCatalogContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSCatalogContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSCatalogContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSCatalogContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{991E5D11-3686-4740-802D-6F17206FD5D0}");}

    /// <summary>Unregisters a class from the GxAGSCatalogContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{991E5D11-3686-4740-802D-6F17206FD5D0}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSDataSpaceObjectContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSDataSpaceObjectContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSDataSpaceObjectContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSDataSpaceObjectContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{201AE7CB-89DF-4FEB-BD31-9F5CFB203B4E}");}

    /// <summary>Unregisters a class from the GxAGSDataSpaceObjectContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{201AE7CB-89DF-4FEB-BD31-9F5CFB203B4E}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSDraftContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSDraftContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSDraftContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSDraftContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{852C6C62-72A4-4AB2-824E-0595A827AD6B}");}

    /// <summary>Unregisters a class from the GxAGSDraftContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{852C6C62-72A4-4AB2-824E-0595A827AD6B}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSDraftMultiSelContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSDraftMultiSelContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSDraftMultiSelContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSDraftMultiSelContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8D582358-9CBD-4EA2-BE44-0630F4200B76}");}

    /// <summary>Unregisters a class from the GxAGSDraftMultiSelContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8D582358-9CBD-4EA2-BE44-0630F4200B76}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FAB5D103-6FB5-4185-8817-13C67FE6ACF3}");}

    /// <summary>Unregisters a class from the GxAGSFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FAB5D103-6FB5-4185-8817-13C67FE6ACF3}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSGeoDataServerContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSGeoDataServerContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSGeoDataServerContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSGeoDataServerContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BA42584B-1EF2-4BE3-B5C7-E7314045B262}");}

    /// <summary>Unregisters a class from the GxAGSGeoDataServerContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BA42584B-1EF2-4BE3-B5C7-E7314045B262}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSGeometryContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSGeometryContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSGeometryContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSGeometryContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EE7EC99E-8BFD-43D9-81FB-0DC6F24A5B36}");}

    /// <summary>Unregisters a class from the GxAGSGeometryContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EE7EC99E-8BFD-43D9-81FB-0DC6F24A5B36}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSGeoprocessingContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSGeoprocessingContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSGeoprocessingContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSGeoprocessingContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F5E6AD59-1D54-4C1C-9CE0-3D3A2FC12071}");}

    /// <summary>Unregisters a class from the GxAGSGeoprocessingContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F5E6AD59-1D54-4C1C-9CE0-3D3A2FC12071}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSGlobeContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSGlobeContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSGlobeContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSGlobeContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2C585B5E-F5CA-4020-A45D-149B26359953}");}

    /// <summary>Unregisters a class from the GxAGSGlobeContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2C585B5E-F5CA-4020-A45D-149B26359953}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSImageContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSImageContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSImageContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSImageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{55832158-565A-45C5-9A66-012EA17A70EB}");}

    /// <summary>Unregisters a class from the GxAGSImageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{55832158-565A-45C5-9A66-012EA17A70EB}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSLocatorContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSLocatorContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSLocatorContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSLocatorContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A65CB7D8-E50F-4965-A41D-C7779C73EAD9}");}

    /// <summary>Unregisters a class from the GxAGSLocatorContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A65CB7D8-E50F-4965-A41D-C7779C73EAD9}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSMapContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSMapContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSMapContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{23ACEAA7-F8E0-4325-B5A2-6649260FEE21}");}

    /// <summary>Unregisters a class from the GxAGSMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{23ACEAA7-F8E0-4325-B5A2-6649260FEE21}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSMultiSelAdminContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSMultiSelAdminContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSMultiSelAdminContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSMultiSelAdminContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8B1F6601-2A12-46E3-9D3F-A1EE93DE4F9B}");}

    /// <summary>Unregisters a class from the GxAGSMultiSelAdminContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8B1F6601-2A12-46E3-9D3F-A1EE93DE4F9B}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSMultiSelContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSMultiSelContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSMultiSelContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSMultiSelContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A8E0313D-8E7A-44E5-A40A-CDFC594A5860}");}

    /// <summary>Unregisters a class from the GxAGSMultiSelContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A8E0313D-8E7A-44E5-A40A-CDFC594A5860}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSObjects component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSObjects class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSObjects : CatReg
  {

    /// <summary>Registers a class to the GxAGSObjects component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EA8FF01B-8BFC-4FE2-B813-F88A1CADC17D}");}

    /// <summary>Unregisters a class from the GxAGSObjects component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EA8FF01B-8BFC-4FE2-B813-F88A1CADC17D}");}
  }

  /// <summary>Registers or unregisters a class to the GxAGSWMServerContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxAGSWMServerContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxAGSWMServerContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxAGSWMServerContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C6DC0899-5B73-4F61-8BE1-FF605151FCF5}");}

    /// <summary>Unregisters a class from the GxAGSWMServerContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C6DC0899-5B73-4F61-8BE1-FF605151FCF5}");}
  }

  /// <summary>Registers or unregisters a class to the GxArchivingMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxArchivingMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxArchivingMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxArchivingMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DB1269D1-6F21-40CF-B2E8-666628324C8D}");}

    /// <summary>Unregisters a class from the GxArchivingMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DB1269D1-6F21-40CF-B2E8-666628324C8D}");}
  }

  /// <summary>Registers or unregisters a class to the GxArcViewExportFeatureClassFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxArcViewExportFeatureClassFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxArcViewExportFeatureClassFilters : CatReg
  {

    /// <summary>Registers a class to the GxArcViewExportFeatureClassFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9EB1D578-740B-423E-8CF4-C77A1775A5D6}");}

    /// <summary>Unregisters a class from the GxArcViewExportFeatureClassFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9EB1D578-740B-423E-8CF4-C77A1775A5D6}");}
  }

  /// <summary>Registers or unregisters a class to the GxArcViewExportTableFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxArcViewExportTableFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxArcViewExportTableFilters : CatReg
  {

    /// <summary>Registers a class to the GxArcViewExportTableFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{593C6231-9B13-4229-A1DF-A7A36F1AE10D}");}

    /// <summary>Unregisters a class from the GxArcViewExportTableFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{593C6231-9B13-4229-A1DF-A7A36F1AE10D}");}
  }

  /// <summary>Registers or unregisters a class to the GxCadastralFabricContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCadastralFabricContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCadastralFabricContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCadastralFabricContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A4101D3C-AC1F-4EF4-A65D-96530A6A1C3C}");}

    /// <summary>Unregisters a class from the GxCadastralFabricContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A4101D3C-AC1F-4EF4-A65D-96530A6A1C3C}");}
  }

  /// <summary>Registers or unregisters a class to the GxCadDataContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCadDataContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCadDataContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCadDataContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9CA-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxCadDataContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9CA-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxCadDrawingContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCadDrawingContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCadDrawingContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCadDrawingContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9C1-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxCadDrawingContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9C1-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxCadDrawingExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCadDrawingExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCadDrawingExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCadDrawingExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9C4-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxCadDrawingExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9C4-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxCadFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCadFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCadFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCadFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9C0-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxCadFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9C0-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxCadFeatureClassExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCadFeatureClassExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCadFeatureClassExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCadFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9C3-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxCadFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9C3-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxCadFeatureContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCadFeatureContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCadFeatureContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCadFeatureContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9BF-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxCadFeatureContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9BF-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxCadFeatureExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCadFeatureExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCadFeatureExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCadFeatureExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83EEE9C2-0CB1-11D3-9B35-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxCadFeatureExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83EEE9C2-0CB1-11D3-9B35-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxCatalogContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCatalogContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCatalogContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCatalogContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F0-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxCatalogContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F0-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxCatalogPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCatalogPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCatalogPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxCatalogPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BD1DF56D-E644-11D2-99C1-0000F80372B4}");}

    /// <summary>Unregisters a class from the GxCatalogPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BD1DF56D-E644-11D2-99C1-0000F80372B4}");}
  }

  /// <summary>Registers or unregisters a class to the GxCommandBars component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCommandBars class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCommandBars : CatReg
  {

    /// <summary>Registers a class to the GxCommandBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{56C205F9-E53A-11D1-9496-080009EEBECB}");}

    /// <summary>Unregisters a class from the GxCommandBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{56C205F9-E53A-11D1-9496-080009EEBECB}");}
  }

  /// <summary>Registers or unregisters a class to the GxCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCommands : CatReg
  {

    /// <summary>Registers a class to the GxCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5F08CBCA-E91F-11D1-AEE8-080009EC734B}");}

    /// <summary>Unregisters a class from the GxCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5F08CBCA-E91F-11D1-AEE8-080009EC734B}");}
  }

  /// <summary>Registers or unregisters a class to the GxCoverageContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCoverageContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCoverageContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCoverageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25B9A22F-E6C7-11D2-9F30-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxCoverageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25B9A22F-E6C7-11D2-9F30-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxCoverageExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCoverageExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCoverageExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCoverageExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A6BF6E97-EB70-11D2-9F31-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxCoverageExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A6BF6E97-EB70-11D2-9F31-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxCoverageFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCoverageFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCoverageFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCoverageFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25B9A230-E6C7-11D2-9F30-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxCoverageFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25B9A230-E6C7-11D2-9F30-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxCoverageFeatureClassExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCoverageFeatureClassExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCoverageFeatureClassExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCoverageFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A6BF6E98-EB70-11D2-9F31-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxCoverageFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A6BF6E98-EB70-11D2-9F31-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxCoverageNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxCoverageNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxCoverageNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxCoverageNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1449254B-319B-11D3-9F33-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxCoverageNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1449254B-319B-11D3-9F33-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxDatabaseContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDatabaseContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDatabaseContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxDatabaseContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F5-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxDatabaseContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F5-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxDatabaseExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDatabaseExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDatabaseExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxDatabaseExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B032F215-D4A4-49B0-BDA0-FFFB21320004}");}

    /// <summary>Unregisters a class from the GxDatabaseExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B032F215-D4A4-49B0-BDA0-FFFB21320004}");}
  }

  /// <summary>Registers or unregisters a class to the GxDatabaseExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDatabaseExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDatabaseExtensions : CatReg
  {

    /// <summary>Registers a class to the GxDatabaseExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6CB2F1D8-4E9D-11D3-9F52-00C04F6BDF06}");}

    /// <summary>Unregisters a class from the GxDatabaseExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6CB2F1D8-4E9D-11D3-9F52-00C04F6BDF06}");}
  }

  /// <summary>Registers or unregisters a class to the GxDatabaseImportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDatabaseImportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDatabaseImportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxDatabaseImportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7513EB97-D7EE-11D2-9F50-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxDatabaseImportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7513EB97-D7EE-11D2-9F50-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxDatabaseNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDatabaseNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDatabaseNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxDatabaseNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E706-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxDatabaseNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E706-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxDataGraphContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDataGraphContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDataGraphContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxDataGraphContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B14315A5-098A-11D4-A676-0008C7DF88DB}");}

    /// <summary>Unregisters a class from the GxDataGraphContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B14315A5-098A-11D4-A676-0008C7DF88DB}");}
  }

  /// <summary>Registers or unregisters a class to the GxDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F7-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F7-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxDialogObjectFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDialogObjectFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDialogObjectFilters : CatReg
  {

    /// <summary>Registers a class to the GxDialogObjectFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BB8F3046-1D26-11D3-9F55-00C04F6BC69E}");}

    /// <summary>Unregisters a class from the GxDialogObjectFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BB8F3046-1D26-11D3-9F55-00C04F6BC69E}");}
  }

  /// <summary>Registers or unregisters a class to the GxDiskConnectionContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDiskConnectionContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDiskConnectionContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxDiskConnectionContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F1-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxDiskConnectionContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F1-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxDockableWindows component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxDockableWindows class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxDockableWindows : CatReg
  {

    /// <summary>Registers a class to the GxDockableWindows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{117623B4-F9D1-11D3-A67F-0008C7DF97B9}");}

    /// <summary>Unregisters a class from the GxDockableWindows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{117623B4-F9D1-11D3-A67F-0008C7DF97B9}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnabledWorkspaceFactories component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnabledWorkspaceFactories class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnabledWorkspaceFactories : CatReg
  {

    /// <summary>Registers a class to the GxEnabledWorkspaceFactories component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6E208C99-DBD3-11D2-9F2F-00C04F6BC69E}");}

    /// <summary>Unregisters a class from the GxEnabledWorkspaceFactories component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6E208C99-DBD3-11D2-9F2F-00C04F6BC69E}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F4EDFE54-E856-4D72-AEC6-7BD59A3E7B52}");}

    /// <summary>Unregisters a class from the GxEnterpriseFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F4EDFE54-E856-4D72-AEC6-7BD59A3E7B52}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseFeatureClassContextMenuCommandsAV component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseFeatureClassContextMenuCommandsAV class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseFeatureClassContextMenuCommandsAV : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseFeatureClassContextMenuCommandsAV component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9648D913-4475-4165-B746-D2058776F9E8}");}

    /// <summary>Unregisters a class from the GxEnterpriseFeatureClassContextMenuCommandsAV component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9648D913-4475-4165-B746-D2058776F9E8}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseFeatureDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseFeatureDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseFeatureDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseFeatureDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DF03366D-F30C-490B-A353-B05BAA18A3AF}");}

    /// <summary>Unregisters a class from the GxEnterpriseFeatureDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DF03366D-F30C-490B-A353-B05BAA18A3AF}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseMosaicDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseMosaicDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseMosaicDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseMosaicDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{995CA057-723E-4D3E-8C4E-21ADD3302C78}");}

    /// <summary>Unregisters a class from the GxEnterpriseMosaicDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{995CA057-723E-4D3E-8C4E-21ADD3302C78}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseRasterBandContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseRasterBandContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseRasterBandContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseRasterBandContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{16685968-2C9E-45A5-9D47-F2DC62942DDE}");}

    /// <summary>Unregisters a class from the GxEnterpriseRasterBandContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{16685968-2C9E-45A5-9D47-F2DC62942DDE}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseRasterDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseRasterDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseRasterDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseRasterDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F2889296-A1EC-4BDF-AEA9-D08D8E0837D9}");}

    /// <summary>Unregisters a class from the GxEnterpriseRasterDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F2889296-A1EC-4BDF-AEA9-D08D8E0837D9}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseRelationshipClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseRelationshipClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseRelationshipClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseRelationshipClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2004CEC9-E2BD-4D2D-8F3F-9E791E7AB106}");}

    /// <summary>Unregisters a class from the GxEnterpriseRelationshipClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2004CEC9-E2BD-4D2D-8F3F-9E791E7AB106}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseStandaloneFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseStandaloneFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseStandaloneFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseStandaloneFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DABA683A-7888-40BE-8E70-49BC0D4F8C30}");}

    /// <summary>Unregisters a class from the GxEnterpriseStandaloneFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DABA683A-7888-40BE-8E70-49BC0D4F8C30}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseStandaloneFeatureClassContextMenuCommandsAV component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseStandaloneFeatureClassContextMenuCommandsAV class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseStandaloneFeatureClassContextMenuCommandsAV : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseStandaloneFeatureClassContextMenuCommandsAV component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{39C1320B-01A5-4D61-B286-2880337B53C4}");}

    /// <summary>Unregisters a class from the GxEnterpriseStandaloneFeatureClassContextMenuCommandsAV component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{39C1320B-01A5-4D61-B286-2880337B53C4}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseTableContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseTableContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseTableContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9B9ACF28-60FE-4ABA-9DC4-5B060A903DF2}");}

    /// <summary>Unregisters a class from the GxEnterpriseTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9B9ACF28-60FE-4ABA-9DC4-5B060A903DF2}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseTableContextMenuCommandsAV component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseTableContextMenuCommandsAV class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseTableContextMenuCommandsAV : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseTableContextMenuCommandsAV component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0273158A-0EA1-4627-B60A-9D3DF568F8F6}");}

    /// <summary>Unregisters a class from the GxEnterpriseTableContextMenuCommandsAV component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0273158A-0EA1-4627-B60A-9D3DF568F8F6}");}
  }

  /// <summary>Registers or unregisters a class to the GxEnterpriseToolboxContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxEnterpriseToolboxContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxEnterpriseToolboxContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxEnterpriseToolboxContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F992AE1F-6C3F-43F4-BD34-95913B50289B}");}

    /// <summary>Unregisters a class from the GxEnterpriseToolboxContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F992AE1F-6C3F-43F4-BD34-95913B50289B}");}
  }

  /// <summary>Registers or unregisters a class to the GxExportFeatureClassFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxExportFeatureClassFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxExportFeatureClassFilters : CatReg
  {

    /// <summary>Registers a class to the GxExportFeatureClassFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8E415006-F854-4ECB-98C3-EFBD68BAF635}");}

    /// <summary>Unregisters a class from the GxExportFeatureClassFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8E415006-F854-4ECB-98C3-EFBD68BAF635}");}
  }

  /// <summary>Registers or unregisters a class to the GxExportTableFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxExportTableFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxExportTableFilters : CatReg
  {

    /// <summary>Registers a class to the GxExportTableFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{260A3656-96D0-417B-AC05-3469A444015A}");}

    /// <summary>Unregisters a class from the GxExportTableFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{260A3656-96D0-417B-AC05-3469A444015A}");}
  }

  /// <summary>Registers or unregisters a class to the GxExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxExtensions : CatReg
  {

    /// <summary>Registers a class to the GxExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4531C69D-DC07-11D2-9F2F-00C04F6BC69E}");}

    /// <summary>Unregisters a class from the GxExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4531C69D-DC07-11D2-9F2F-00C04F6BC69E}");}
  }

  /// <summary>Registers or unregisters a class to the GxExtensionsJIT component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxExtensionsJIT class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxExtensionsJIT : CatReg
  {

    /// <summary>Registers a class to the GxExtensionsJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E72DB9D2-D842-4AA5-9D7F-1B70EA2F0A10}");}

    /// <summary>Unregisters a class from the GxExtensionsJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E72DB9D2-D842-4AA5-9D7F-1B70EA2F0A10}");}
  }

  /// <summary>Registers or unregisters a class to the GxExtensionToolbar component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxExtensionToolbar class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxExtensionToolbar : CatReg
  {

    /// <summary>Registers a class to the GxExtensionToolbar component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{58374DA9-3A52-11D3-9F70-00C04F6BC69E}");}

    /// <summary>Unregisters a class from the GxExtensionToolbar component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{58374DA9-3A52-11D3-9F70-00C04F6BC69E}");}
  }

  /// <summary>Registers or unregisters a class to the GxFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F9-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F9-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFeatureClassExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFeatureClassExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFeatureClassExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7513EB9B-D7EE-11D2-9F50-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7513EB9B-D7EE-11D2-9F50-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFeatureDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFeatureDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFeatureDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFeatureDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F8-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFeatureDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F8-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFeatureDatasetExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFeatureDatasetExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFeatureDatasetExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFeatureDatasetExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7513EB9A-D7EE-11D2-9F50-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFeatureDatasetExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7513EB9A-D7EE-11D2-9F50-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFeatureDatasetImportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFeatureDatasetImportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFeatureDatasetImportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFeatureDatasetImportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7513EB99-D7EE-11D2-9F50-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFeatureDatasetImportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7513EB99-D7EE-11D2-9F50-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFeatureDatasetNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFeatureDatasetNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFeatureDatasetNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFeatureDatasetNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E707-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFeatureDatasetNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E707-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFileContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFileContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFileContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFileContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E700-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFileContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E700-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFilterFeatureClasses component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFilterFeatureClasses class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFilterFeatureClasses : CatReg
  {

    /// <summary>Registers a class to the GxFilterFeatureClasses component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FBFDAC87-FE57-4ABA-B5AA-571C78B6399D}");}

    /// <summary>Unregisters a class from the GxFilterFeatureClasses component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FBFDAC87-FE57-4ABA-B5AA-571C78B6399D}");}
  }

  /// <summary>Registers or unregisters a class to the GxFilterFeatureDatasets component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFilterFeatureDatasets class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFilterFeatureDatasets : CatReg
  {

    /// <summary>Registers a class to the GxFilterFeatureDatasets component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3EB92610-DB62-465E-A326-8E0E71C24C20}");}

    /// <summary>Unregisters a class from the GxFilterFeatureDatasets component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3EB92610-DB62-465E-A326-8E0E71C24C20}");}
  }

  /// <summary>Registers or unregisters a class to the GxFilterTables component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFilterTables class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFilterTables : CatReg
  {

    /// <summary>Registers a class to the GxFilterTables component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5FC6B144-22A8-487F-A208-67C34877F120}");}

    /// <summary>Unregisters a class from the GxFilterTables component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5FC6B144-22A8-487F-A208-67C34877F120}");}
  }

  /// <summary>Registers or unregisters a class to the GxFolderConnectionsContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFolderConnectionsContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFolderConnectionsContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFolderConnectionsContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D057B230-029E-4D27-94C9-A16C81FF4C6B}");}

    /// <summary>Unregisters a class from the GxFolderConnectionsContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D057B230-029E-4D27-94C9-A16C81FF4C6B}");}
  }

  /// <summary>Registers or unregisters a class to the GxFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F4-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F4-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFolderNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFolderNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFolderNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxFolderNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E705-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxFolderNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E705-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxFolderNewMenuCommandsAV component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxFolderNewMenuCommandsAV class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxFolderNewMenuCommandsAV : CatReg
  {

    /// <summary>Registers a class to the GxFolderNewMenuCommandsAV component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1A9A50A4-F123-4CEC-93DC-8AF1CE0CDDA0}");}

    /// <summary>Unregisters a class from the GxFolderNewMenuCommandsAV component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1A9A50A4-F123-4CEC-93DC-8AF1CE0CDDA0}");}
  }

  /// <summary>Registers or unregisters a class to the GxGeometricNetworkContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxGeometricNetworkContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxGeometricNetworkContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxGeometricNetworkContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6FB-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxGeometricNetworkContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6FB-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxGeoprocessingResultContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxGeoprocessingResultContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxGeoprocessingResultContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxGeoprocessingResultContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C5C2E162-6F5D-4BE5-88B4-A9BAF56B4D11}");}

    /// <summary>Unregisters a class from the GxGeoprocessingResultContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C5C2E162-6F5D-4BE5-88B4-A9BAF56B4D11}");}
  }

  /// <summary>Registers or unregisters a class to the GxGlobeContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxGlobeContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxGlobeContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxGlobeContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21E4-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GxGlobeContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21E4-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GxGlobePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxGlobePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxGlobePropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxGlobePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{720E21E3-2199-11D6-B2B3-00508BCDDE28}");}

    /// <summary>Unregisters a class from the GxGlobePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{720E21E3-2199-11D6-B2B3-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the GxGridContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxGridContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxGridContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxGridContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6FE-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxGridContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6FE-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxInfoTableContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxInfoTableContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxInfoTableContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxInfoTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25B9A231-E6C7-11D2-9F30-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxInfoTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25B9A231-E6C7-11D2-9F30-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxInfoTableExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxInfoTableExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxInfoTableExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxInfoTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A6BF6E99-EB70-11D2-9F31-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxInfoTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A6BF6E99-EB70-11D2-9F31-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxInfoTableToFeatureClassMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxInfoTableToFeatureClassMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxInfoTableToFeatureClassMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxInfoTableToFeatureClassMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{506187AA-301B-11D4-9FC8-00C04F6BDF06}");}

    /// <summary>Unregisters a class from the GxInfoTableToFeatureClassMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{506187AA-301B-11D4-9FC8-00C04F6BDF06}");}
  }

  /// <summary>Registers or unregisters a class to the GxLayerContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxLayerContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxLayerContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxLayerContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E702-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxLayerContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E702-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxLayerFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxLayerFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxLayerFilters : CatReg
  {

    /// <summary>Registers a class to the GxLayerFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C2C372C2-1EB4-4101-9A38-992536A5C0D0}");}

    /// <summary>Unregisters a class from the GxLayerFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C2C372C2-1EB4-4101-9A38-992536A5C0D0}");}
  }

  /// <summary>Registers or unregisters a class to the GxLocatorContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxLocatorContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxLocatorContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxLocatorContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{940C2D60-4AAD-11D3-9F51-00C04F6BDF06}");}

    /// <summary>Unregisters a class from the GxLocatorContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{940C2D60-4AAD-11D3-9F51-00C04F6BDF06}");}
  }

  /// <summary>Registers or unregisters a class to the GxLocatorFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxLocatorFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxLocatorFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxLocatorFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E62D6CB4-4AB0-11D3-9F51-00C04F6BDF06}");}

    /// <summary>Unregisters a class from the GxLocatorFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E62D6CB4-4AB0-11D3-9F51-00C04F6BDF06}");}
  }

  /// <summary>Registers or unregisters a class to the GxLocatorMenus component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxLocatorMenus class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxLocatorMenus : CatReg
  {

    /// <summary>Registers a class to the GxLocatorMenus component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{55EFFA76-622C-11D3-9F60-00C04F8ED1C4}");}

    /// <summary>Unregisters a class from the GxLocatorMenus component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{55EFFA76-622C-11D3-9F60-00C04F8ED1C4}");}
  }

  /// <summary>Registers or unregisters a class to the GxMapContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMapContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMapContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E703-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E703-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxMapPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMapPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMapPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxMapPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2044F8C9-D8D7-11D2-99BE-0000F80372B4}");}

    /// <summary>Unregisters a class from the GxMapPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2044F8C9-D8D7-11D2-99BE-0000F80372B4}");}
  }

  /// <summary>Registers or unregisters a class to the GxMetadataExporter component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMetadataExporter class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMetadataExporter : CatReg
  {

    /// <summary>Registers a class to the GxMetadataExporter component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E5FB4CF2-660C-11D3-A68B-0008C7D3AE50}");}

    /// <summary>Unregisters a class from the GxMetadataExporter component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E5FB4CF2-660C-11D3-A68B-0008C7D3AE50}");}
  }

  /// <summary>Registers or unregisters a class to the GxMetadataImporter component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMetadataImporter class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMetadataImporter : CatReg
  {

    /// <summary>Registers a class to the GxMetadataImporter component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E5FB4CF1-660C-11D3-A68B-0008C7D3AE50}");}

    /// <summary>Unregisters a class from the GxMetadataImporter component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E5FB4CF1-660C-11D3-A68B-0008C7D3AE50}");}
  }

  /// <summary>Registers or unregisters a class to the GxMosaicDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMosaicDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMosaicDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxMosaicDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{37906F42-FE82-42E9-8E47-0E6FED53DCEA}");}

    /// <summary>Unregisters a class from the GxMosaicDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{37906F42-FE82-42E9-8E47-0E6FED53DCEA}");}
  }

  /// <summary>Registers or unregisters a class to the GxMSDFileContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMSDFileContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMSDFileContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxMSDFileContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2F628DAC-36EE-474C-94EC-3B41E8CDBAD7}");}

    /// <summary>Unregisters a class from the GxMSDFileContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2F628DAC-36EE-474C-94EC-3B41E8CDBAD7}");}
  }

  /// <summary>Registers or unregisters a class to the GxMSDFilePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMSDFilePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMSDFilePropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxMSDFilePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B3F9C298-D73F-4485-B831-2E2687AC6010}");}

    /// <summary>Unregisters a class from the GxMSDFilePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B3F9C298-D73F-4485-B831-2E2687AC6010}");}
  }

  /// <summary>Registers or unregisters a class to the GxMultipleSelectionContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMultipleSelectionContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMultipleSelectionContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxMultipleSelectionContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{35DB0ACD-1DAF-11D3-9FAE-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxMultipleSelectionContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{35DB0ACD-1DAF-11D3-9FAE-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxMultipleSelectionExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMultipleSelectionExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMultipleSelectionExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxMultipleSelectionExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3236816E-9515-4F06-BA58-878010A5285E}");}

    /// <summary>Unregisters a class from the GxMultipleSelectionExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3236816E-9515-4F06-BA58-878010A5285E}");}
  }

  /// <summary>Registers or unregisters a class to the GxMXTMapContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMXTMapContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMXTMapContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxMXTMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EDC99D57-34BE-4EE8-984F-F43C49D2491B}");}

    /// <summary>Unregisters a class from the GxMXTMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EDC99D57-34BE-4EE8-984F-F43C49D2491B}");}
  }

  /// <summary>Registers or unregisters a class to the GxMyHostedMapsFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxMyHostedMapsFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxMyHostedMapsFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxMyHostedMapsFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{92944360-DC2E-4AB7-978B-9B6F37140FE3}");}

    /// <summary>Unregisters a class from the GxMyHostedMapsFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{92944360-DC2E-4AB7-978B-9B6F37140FE3}");}
  }

  /// <summary>Registers or unregisters a class to the GxNetworkDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxNetworkDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxNetworkDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxNetworkDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{34E1368B-5FC5-45E0-9767-31CB0E7D4714}");}

    /// <summary>Unregisters a class from the GxNetworkDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{34E1368B-5FC5-45E0-9767-31CB0E7D4714}");}
  }

  /// <summary>Registers or unregisters a class to the GxObjectFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxObjectFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxObjectFactory : CatReg
  {

    /// <summary>Registers a class to the GxObjectFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{65D77504-895C-11D2-AF5D-080009EC734B}");}

    /// <summary>Unregisters a class from the GxObjectFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{65D77504-895C-11D2-AF5D-080009EC734B}");}
  }

  /// <summary>Registers or unregisters a class to the GxObjectFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxObjectFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxObjectFilters : CatReg
  {

    /// <summary>Registers a class to the GxObjectFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BB8F3045-1D26-11D3-9F55-00C04F6BC69E}");}

    /// <summary>Unregisters a class from the GxObjectFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BB8F3045-1D26-11D3-9F55-00C04F6BC69E}");}
  }

  /// <summary>Registers or unregisters a class to the GxOleDBDatabaseContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxOleDBDatabaseContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxOleDBDatabaseContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxOleDBDatabaseContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8F4CFA6B-B38E-4E4B-9AB1-E1AFB3CBB569}");}

    /// <summary>Unregisters a class from the GxOleDBDatabaseContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8F4CFA6B-B38E-4E4B-9AB1-E1AFB3CBB569}");}
  }

  /// <summary>Registers or unregisters a class to the GxOleDBTableContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxOleDBTableContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxOleDBTableContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxOleDBTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{44C34C54-E41B-40EF-AC63-8D25A9FC01FA}");}

    /// <summary>Unregisters a class from the GxOleDBTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{44C34C54-E41B-40EF-AC63-8D25A9FC01FA}");}
  }

  /// <summary>Registers or unregisters a class to the GxPackageContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPackageContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPackageContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxPackageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{760041EF-3BAC-4167-B7C7-A52051A9E404}");}

    /// <summary>Unregisters a class from the GxPackageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{760041EF-3BAC-4167-B7C7-A52051A9E404}");}
  }

  /// <summary>Registers or unregisters a class to the GxPackagePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPackagePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPackagePropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxPackagePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{065188C9-4749-429F-9E39-A9B76313EFF9}");}

    /// <summary>Unregisters a class from the GxPackagePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{065188C9-4749-429F-9E39-A9B76313EFF9}");}
  }

  /// <summary>Registers or unregisters a class to the GxPalettes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPalettes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPalettes : CatReg
  {

    /// <summary>Registers a class to the GxPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5F08CBCB-E91F-11D1-AEE8-080009EC734B}");}

    /// <summary>Unregisters a class from the GxPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5F08CBCB-E91F-11D1-AEE8-080009EC734B}");}
  }

  /// <summary>Registers or unregisters a class to the GxPCCoverageContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPCCoverageContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPCCoverageContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxPCCoverageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4B6C687E-66D2-11D3-9F36-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxPCCoverageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4B6C687E-66D2-11D3-9F36-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxPCCoverageFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPCCoverageFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPCCoverageFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxPCCoverageFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4B6C687F-66D2-11D3-9F36-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxPCCoverageFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4B6C687F-66D2-11D3-9F36-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxPMFMapContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPMFMapContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPMFMapContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxPMFMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F7F3ABF6-FB3C-4E7F-9F38-D45DCDF5F30C}");}

    /// <summary>Unregisters a class from the GxPMFMapContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F7F3ABF6-FB3C-4E7F-9F38-D45DCDF5F30C}");}
  }

  /// <summary>Registers or unregisters a class to the GxPMFMapPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPMFMapPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPMFMapPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxPMFMapPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C00B1F2C-52D1-404F-8DD5-E3694FD60E00}");}

    /// <summary>Unregisters a class from the GxPMFMapPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C00B1F2C-52D1-404F-8DD5-E3694FD60E00}");}
  }

  /// <summary>Registers or unregisters a class to the GxPre70CoverageContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPre70CoverageContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPre70CoverageContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxPre70CoverageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C65A2BB4-32ED-11D3-9F33-00C04F79927C}");}

    /// <summary>Unregisters a class from the GxPre70CoverageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C65A2BB4-32ED-11D3-9F33-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the GxPreviews component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPreviews class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPreviews : CatReg
  {

    /// <summary>Registers a class to the GxPreviews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3EEA2CB0-A730-11D2-AF6D-080009EC734B}");}

    /// <summary>Unregisters a class from the GxPreviews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3EEA2CB0-A730-11D2-AF6D-080009EC734B}");}
  }

  /// <summary>Registers or unregisters a class to the GxPrjFileContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxPrjFileContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxPrjFileContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxPrjFileContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E701-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxPrjFileContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E701-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxRasterBandContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRasterBandContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRasterBandContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxRasterBandContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6FD-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxRasterBandContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6FD-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxRasterCatalogContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRasterCatalogContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRasterCatalogContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxRasterCatalogContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CDD15DB8-E364-4A0B-A6E8-2D111CA4E92D}");}

    /// <summary>Unregisters a class from the GxRasterCatalogContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CDD15DB8-E364-4A0B-A6E8-2D111CA4E92D}");}
  }

  /// <summary>Registers or unregisters a class to the GxRasterCatalogFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRasterCatalogFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRasterCatalogFilters : CatReg
  {

    /// <summary>Registers a class to the GxRasterCatalogFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{683FB8AE-517B-47BB-9C00-F89015ADAB60}");}

    /// <summary>Unregisters a class from the GxRasterCatalogFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{683FB8AE-517B-47BB-9C00-F89015ADAB60}");}
  }

  /// <summary>Registers or unregisters a class to the GxRasterCatalogItemContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRasterCatalogItemContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRasterCatalogItemContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxRasterCatalogItemContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{549B0B62-95CF-4D99-BB69-B18D05DA40A1}");}

    /// <summary>Unregisters a class from the GxRasterCatalogItemContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{549B0B62-95CF-4D99-BB69-B18D05DA40A1}");}
  }

  /// <summary>Registers or unregisters a class to the GxRasterCatalogViews component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRasterCatalogViews class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRasterCatalogViews : CatReg
  {

    /// <summary>Registers a class to the GxRasterCatalogViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{699AD2EC-FE3E-493C-9112-4B18E2CEC0D6}");}

    /// <summary>Unregisters a class from the GxRasterCatalogViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{699AD2EC-FE3E-493C-9112-4B18E2CEC0D6}");}
  }

  /// <summary>Registers or unregisters a class to the GxRasterDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRasterDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRasterDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxRasterDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6FC-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxRasterDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6FC-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxReadOnlyFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxReadOnlyFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxReadOnlyFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxReadOnlyFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A44C92BC-79D6-4F89-A0A8-40CDCC279EDC}");}

    /// <summary>Unregisters a class from the GxReadOnlyFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A44C92BC-79D6-4F89-A0A8-40CDCC279EDC}");}
  }

  /// <summary>Registers or unregisters a class to the GxReadOnlyFeatureDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxReadOnlyFeatureDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxReadOnlyFeatureDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxReadOnlyFeatureDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5484E3DE-86FB-489C-8EB1-73EC4A0E4485}");}

    /// <summary>Unregisters a class from the GxReadOnlyFeatureDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5484E3DE-86FB-489C-8EB1-73EC4A0E4485}");}
  }

  /// <summary>Registers or unregisters a class to the GxReadOnlyNetworkContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxReadOnlyNetworkContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxReadOnlyNetworkContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxReadOnlyNetworkContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4EFCD3A2-F27F-4F60-953B-74BCB0736514}");}

    /// <summary>Unregisters a class from the GxReadOnlyNetworkContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4EFCD3A2-F27F-4F60-953B-74BCB0736514}");}
  }

  /// <summary>Registers or unregisters a class to the GxReadOnlyStandaloneFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxReadOnlyStandaloneFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxReadOnlyStandaloneFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxReadOnlyStandaloneFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D1E6735C-4464-4875-8673-59D94A603C3C}");}

    /// <summary>Unregisters a class from the GxReadOnlyStandaloneFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D1E6735C-4464-4875-8673-59D94A603C3C}");}
  }

  /// <summary>Registers or unregisters a class to the GxReadOnlyTableContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxReadOnlyTableContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxReadOnlyTableContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxReadOnlyTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3BF096DF-B346-46AF-99E2-AFB52ED90F4E}");}

    /// <summary>Unregisters a class from the GxReadOnlyTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3BF096DF-B346-46AF-99E2-AFB52ED90F4E}");}
  }

  /// <summary>Registers or unregisters a class to the GxRelationshipClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRelationshipClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRelationshipClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxRelationshipClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6C9CB46D-DCA2-11D2-9F54-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxRelationshipClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6C9CB46D-DCA2-11D2-9F54-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxRemoteDatabaseContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRemoteDatabaseContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRemoteDatabaseContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxRemoteDatabaseContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F6-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxRemoteDatabaseContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F6-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxRemoteDatabaseFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRemoteDatabaseFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRemoteDatabaseFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxRemoteDatabaseFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F2-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxRemoteDatabaseFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F2-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxRootObjects component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxRootObjects class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxRootObjects : CatReg
  {

    /// <summary>Registers a class to the GxRootObjects component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6E208C9A-DBD3-11D2-9F2F-00C04F6BC69E}");}

    /// <summary>Unregisters a class from the GxRootObjects component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6E208C9A-DBD3-11D2-9F2F-00C04F6BC69E}");}
  }

  /// <summary>Registers or unregisters a class to the GxSceneContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSceneContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSceneContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSceneContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3E804E72-8FE3-11D4-AB88-0008C73FD50C}");}

    /// <summary>Unregisters a class from the GxSceneContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3E804E72-8FE3-11D4-AB88-0008C73FD50C}");}
  }

  /// <summary>Registers or unregisters a class to the GxScenePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxScenePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxScenePropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxScenePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A72131C2-90FA-11D4-AB88-0008C73FD50C}");}

    /// <summary>Unregisters a class from the GxScenePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A72131C2-90FA-11D4-AB88-0008C73FD50C}");}
  }

  /// <summary>Registers or unregisters a class to the GxSchematicDatasetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSchematicDatasetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSchematicDatasetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSchematicDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F3756085-8657-49EC-906D-ECB7CD0920A4}");}

    /// <summary>Unregisters a class from the GxSchematicDatasetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F3756085-8657-49EC-906D-ECB7CD0920A4}");}
  }

  /// <summary>Registers or unregisters a class to the GxSchematicDatasetExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSchematicDatasetExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSchematicDatasetExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSchematicDatasetExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AF648EAA-F94A-4307-928B-C4DC2B7555C7}");}

    /// <summary>Unregisters a class from the GxSchematicDatasetExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AF648EAA-F94A-4307-928B-C4DC2B7555C7}");}
  }

  /// <summary>Registers or unregisters a class to the GxSchematicDatasetNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSchematicDatasetNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSchematicDatasetNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSchematicDatasetNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A16670E7-25F8-4C08-BFEB-33501DFEF120}");}

    /// <summary>Unregisters a class from the GxSchematicDatasetNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A16670E7-25F8-4C08-BFEB-33501DFEF120}");}
  }

  /// <summary>Registers or unregisters a class to the GxSchematicDiagramContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSchematicDiagramContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSchematicDiagramContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSchematicDiagramContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3B1FD8BD-FF79-4CE3-B0B2-83F2319BDE52}");}

    /// <summary>Unregisters a class from the GxSchematicDiagramContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3B1FD8BD-FF79-4CE3-B0B2-83F2319BDE52}");}
  }

  /// <summary>Registers or unregisters a class to the GxSchematicFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSchematicFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSchematicFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSchematicFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9D65F80B-FA2A-4093-A259-59FDEFE78068}");}

    /// <summary>Unregisters a class from the GxSchematicFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9D65F80B-FA2A-4093-A259-59FDEFE78068}");}
  }

  /// <summary>Registers or unregisters a class to the GxSchematicFolderNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSchematicFolderNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSchematicFolderNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSchematicFolderNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0BCA803D-BCF6-49D1-9749-2157D083CC52}");}

    /// <summary>Unregisters a class from the GxSchematicFolderNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0BCA803D-BCF6-49D1-9749-2157D083CC52}");}
  }

  /// <summary>Registers or unregisters a class to the GxSDCFeatureClassExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSDCFeatureClassExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSDCFeatureClassExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSDCFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{95BCD5A1-8C27-4ACE-9675-BFF5391CE339}");}

    /// <summary>Unregisters a class from the GxSDCFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{95BCD5A1-8C27-4ACE-9675-BFF5391CE339}");}
  }

  /// <summary>Registers or unregisters a class to the GxSDCTableExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSDCTableExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSDCTableExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSDCTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{291B2148-0495-43AC-9108-F9891917A0D1}");}

    /// <summary>Unregisters a class from the GxSDCTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{291B2148-0495-43AC-9108-F9891917A0D1}");}
  }

  /// <summary>Registers or unregisters a class to the GxSearchEngines component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSearchEngines class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSearchEngines : CatReg
  {

    /// <summary>Registers a class to the GxSearchEngines component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1236649F-CD2B-11D3-A6F0-0008C7D3AE50}");}

    /// <summary>Unregisters a class from the GxSearchEngines component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1236649F-CD2B-11D3-A6F0-0008C7D3AE50}");}
  }

  /// <summary>Registers or unregisters a class to the GxServiceDefinitionContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxServiceDefinitionContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxServiceDefinitionContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxServiceDefinitionContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DA3F9900-09B0-42DF-92FB-4960A000965D}");}

    /// <summary>Unregisters a class from the GxServiceDefinitionContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DA3F9900-09B0-42DF-92FB-4960A000965D}");}
  }

  /// <summary>Registers or unregisters a class to the GxServiceDefinitionMultiSelContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxServiceDefinitionMultiSelContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxServiceDefinitionMultiSelContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxServiceDefinitionMultiSelContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D7FCBDDA-F6E5-4EB7-852F-1C6855BC1BC5}");}

    /// <summary>Unregisters a class from the GxServiceDefinitionMultiSelContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D7FCBDDA-F6E5-4EB7-852F-1C6855BC1BC5}");}
  }

  /// <summary>Registers or unregisters a class to the GxShapefileFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxShapefileFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxShapefileFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxShapefileFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E10D6EC0-06E6-11D3-9F87-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxShapefileFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E10D6EC0-06E6-11D3-9F87-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxShapefileFeatureClassExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxShapefileFeatureClassExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxShapefileFeatureClassExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxShapefileFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E10D6EC2-06E6-11D3-9F87-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxShapefileFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E10D6EC2-06E6-11D3-9F87-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxShapefileTableContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxShapefileTableContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxShapefileTableContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxShapefileTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E10D6EC1-06E6-11D3-9F87-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxShapefileTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E10D6EC1-06E6-11D3-9F87-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxShapefileTableExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxShapefileTableExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxShapefileTableExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxShapefileTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E10D6EC3-06E6-11D3-9F87-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxShapefileTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E10D6EC3-06E6-11D3-9F87-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxShapefileTableToFeatureClassMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxShapefileTableToFeatureClassMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxShapefileTableToFeatureClassMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxShapefileTableToFeatureClassMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{124C8C26-301B-11D4-9FC8-00C04F6BDF06}");}

    /// <summary>Unregisters a class from the GxShapefileTableToFeatureClassMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{124C8C26-301B-11D4-9FC8-00C04F6BDF06}");}
  }

  /// <summary>Registers or unregisters a class to the GxShortcutContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxShortcutContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxShortcutContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxShortcutContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AB6C1071-13FC-4274-8287-A8AA35A1011A}");}

    /// <summary>Unregisters a class from the GxShortcutContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AB6C1071-13FC-4274-8287-A8AA35A1011A}");}
  }

  /// <summary>Registers or unregisters a class to the GxSpatialReferencesFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSpatialReferencesFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSpatialReferencesFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSpatialReferencesFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6F3-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxSpatialReferencesFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6F3-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxSpatialReferencesFolderNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSpatialReferencesFolderNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSpatialReferencesFolderNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSpatialReferencesFolderNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9828BC65-3AD7-11D3-A62F-0008C7D3AE8D}");}

    /// <summary>Unregisters a class from the GxSpatialReferencesFolderNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9828BC65-3AD7-11D3-A62F-0008C7D3AE8D}");}
  }

  /// <summary>Registers or unregisters a class to the GxSqlFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSqlFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSqlFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSqlFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B9BF4AEC-B681-4BFF-955C-A11EB028973E}");}

    /// <summary>Unregisters a class from the GxSqlFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B9BF4AEC-B681-4BFF-955C-A11EB028973E}");}
  }

  /// <summary>Registers or unregisters a class to the GxSqlTableContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxSqlTableContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxSqlTableContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxSqlTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C1231B80-2EB9-42E1-9065-8B39706BE65E}");}

    /// <summary>Unregisters a class from the GxSqlTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C1231B80-2EB9-42E1-9065-8B39706BE65E}");}
  }

  /// <summary>Registers or unregisters a class to the GxStandaloneFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxStandaloneFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxStandaloneFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxStandaloneFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{22211295-7778-11D3-A00D-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxStandaloneFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{22211295-7778-11D3-A00D-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxStreetMapFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxStreetMapFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxStreetMapFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxStreetMapFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3B5C1D75-C440-4EBF-B629-ACCAD41BF396}");}

    /// <summary>Unregisters a class from the GxStreetMapFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3B5C1D75-C440-4EBF-B629-ACCAD41BF396}");}
  }

  /// <summary>Registers or unregisters a class to the GxStreetMapFeatureClassExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxStreetMapFeatureClassExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxStreetMapFeatureClassExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxStreetMapFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5DBC42A8-3F19-4138-BDFE-C8EB60456A0F}");}

    /// <summary>Unregisters a class from the GxStreetMapFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5DBC42A8-3F19-4138-BDFE-C8EB60456A0F}");}
  }

  /// <summary>Registers or unregisters a class to the GxStreetMapFeatureClassPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxStreetMapFeatureClassPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxStreetMapFeatureClassPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxStreetMapFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F1B979F7-AE98-478A-8A80-C731B8C8F3E9}");}

    /// <summary>Unregisters a class from the GxStreetMapFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F1B979F7-AE98-478A-8A80-C731B8C8F3E9}");}
  }

  /// <summary>Registers or unregisters a class to the GxTableAttachmentsMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTableAttachmentsMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTableAttachmentsMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxTableAttachmentsMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DE36981B-AE70-4E74-8D4E-DB5E8D236F11}");}

    /// <summary>Unregisters a class from the GxTableAttachmentsMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DE36981B-AE70-4E74-8D4E-DB5E8D236F11}");}
  }

  /// <summary>Registers or unregisters a class to the GxTableContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTableContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTableContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6FA-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6FA-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxTableExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTableExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTableExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{16FD2B1D-1556-11D3-9FA7-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{16FD2B1D-1556-11D3-9FA7-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxTableToFeatureClassMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTableToFeatureClassMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTableToFeatureClassMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxTableToFeatureClassMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{20580FBF-2DDE-11D4-9FC8-00C04F6BDF06}");}

    /// <summary>Unregisters a class from the GxTableToFeatureClassMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{20580FBF-2DDE-11D4-9FC8-00C04F6BDF06}");}
  }

  /// <summary>Registers or unregisters a class to the GxTabViews component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTabViews class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTabViews : CatReg
  {

    /// <summary>Registers a class to the GxTabViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3EEA2CAF-A730-11D2-AF6D-080009EC734B}");}

    /// <summary>Unregisters a class from the GxTabViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3EEA2CAF-A730-11D2-AF6D-080009EC734B}");}
  }

  /// <summary>Registers or unregisters a class to the GxTaskServicesRootFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTaskServicesRootFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTaskServicesRootFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxTaskServicesRootFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DDA15A86-5B58-47CD-8867-8116CCCFD847}");}

    /// <summary>Unregisters a class from the GxTaskServicesRootFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DDA15A86-5B58-47CD-8867-8116CCCFD847}");}
  }

  /// <summary>Registers or unregisters a class to the GxTerrainContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTerrainContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTerrainContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxTerrainContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6F039D8D-2804-42A1-A0F0-D01CF0D0FE20}");}

    /// <summary>Unregisters a class from the GxTerrainContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6F039D8D-2804-42A1-A0F0-D01CF0D0FE20}");}
  }

  /// <summary>Registers or unregisters a class to the GxTinContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTinContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTinContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxTinContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{25C0E6FF-CD06-11D2-9F40-00C04F6BC626}");}

    /// <summary>Unregisters a class from the GxTinContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{25C0E6FF-CD06-11D2-9F40-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolboxAddMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolboxAddMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolboxAddMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolboxAddMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C64A9BAF-B0F1-4FA1-8663-98752C4FAA24}");}

    /// <summary>Unregisters a class from the GxToolboxAddMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C64A9BAF-B0F1-4FA1-8663-98752C4FAA24}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolboxContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolboxContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolboxContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolboxContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F039FC65-859F-4F38-AFD4-28590C3CFDDE}");}

    /// <summary>Unregisters a class from the GxToolboxContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F039FC65-859F-4F38-AFD4-28590C3CFDDE}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolboxesFolderContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolboxesFolderContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolboxesFolderContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolboxesFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{795E26E5-A5F4-4A82-AF45-EFA8BB6BC637}");}

    /// <summary>Unregisters a class from the GxToolboxesFolderContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{795E26E5-A5F4-4A82-AF45-EFA8BB6BC637}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolboxesFolderNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolboxesFolderNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolboxesFolderNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolboxesFolderNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9EEC0A0C-9ED4-42D4-8FC8-4CC4C7E25EAD}");}

    /// <summary>Unregisters a class from the GxToolboxesFolderNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9EEC0A0C-9ED4-42D4-8FC8-4CC4C7E25EAD}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolboxNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolboxNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolboxNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolboxNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{502D09BC-37CF-4A2C-B84C-9C8AC6A6F499}");}

    /// <summary>Unregisters a class from the GxToolboxNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{502D09BC-37CF-4A2C-B84C-9C8AC6A6F499}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{301C24FF-4817-4660-8028-E9906827592C}");}

    /// <summary>Unregisters a class from the GxToolContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{301C24FF-4817-4660-8028-E9906827592C}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolsetAddMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolsetAddMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolsetAddMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolsetAddMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D46149BC-9194-4D53-A0E8-5BB8D951FAC3}");}

    /// <summary>Unregisters a class from the GxToolsetAddMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D46149BC-9194-4D53-A0E8-5BB8D951FAC3}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolsetContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolsetContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolsetContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolsetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8C30CDA6-6124-4E49-88F1-8E6F8C831A2D}");}

    /// <summary>Unregisters a class from the GxToolsetContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8C30CDA6-6124-4E49-88F1-8E6F8C831A2D}");}
  }

  /// <summary>Registers or unregisters a class to the GxToolsetNewMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxToolsetNewMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxToolsetNewMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxToolsetNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{09D5B1A2-1208-4C12-A53A-18722A83E1D4}");}

    /// <summary>Unregisters a class from the GxToolsetNewMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{09D5B1A2-1208-4C12-A53A-18722A83E1D4}");}
  }

  /// <summary>Registers or unregisters a class to the GxTopologyContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxTopologyContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxTopologyContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxTopologyContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0484A5EC-4701-4B65-A097-A991D931C4CC}");}

    /// <summary>Unregisters a class from the GxTopologyContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0484A5EC-4701-4B65-A097-A991D931C4CC}");}
  }

  /// <summary>Registers or unregisters a class to the GxViews component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxViews class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxViews : CatReg
  {

    /// <summary>Registers a class to the GxViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3EEA2CB1-A730-11D2-AF6D-080009EC734B}");}

    /// <summary>Unregisters a class from the GxViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3EEA2CB1-A730-11D2-AF6D-080009EC734B}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfCoverageContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfCoverageContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfCoverageContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxVpfCoverageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{832A7CA1-F47F-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfCoverageContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{832A7CA1-F47F-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfCoverageExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfCoverageExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfCoverageExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxVpfCoverageExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{832A7CA3-F47F-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfCoverageExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{832A7CA3-F47F-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfCoveragePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfCoveragePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfCoveragePropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxVpfCoveragePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{832A7CA5-F47F-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfCoveragePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{832A7CA5-F47F-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfFeatureClassContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfFeatureClassContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfFeatureClassContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxVpfFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{832A7CA2-F47F-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfFeatureClassContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{832A7CA2-F47F-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfFeatureClassExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfFeatureClassExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfFeatureClassExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxVpfFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{832A7CA4-F47F-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfFeatureClassExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{832A7CA4-F47F-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfFeatureClassPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfFeatureClassPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfFeatureClassPropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxVpfFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{832A7CA6-F47F-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{832A7CA6-F47F-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfTableContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfTableContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfTableContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxVpfTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1CB448E4-F485-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfTableContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1CB448E4-F485-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfTableExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfTableExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfTableExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxVpfTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1CB448E5-F485-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfTableExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1CB448E5-F485-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxVpfTablePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxVpfTablePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxVpfTablePropertyPages : CatReg
  {

    /// <summary>Registers a class to the GxVpfTablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1CB448E6-F485-11D3-9B56-00C04FA33299}");}

    /// <summary>Unregisters a class from the GxVpfTablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1CB448E6-F485-11D3-9B56-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the GxWCSCoveragePropertiesPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxWCSCoveragePropertiesPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxWCSCoveragePropertiesPage : CatReg
  {

    /// <summary>Registers a class to the GxWCSCoveragePropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{002C8AEC-0188-403D-B55C-07BC0E430C83}");}

    /// <summary>Unregisters a class from the GxWCSCoveragePropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{002C8AEC-0188-403D-B55C-07BC0E430C83}");}
  }

  /// <summary>Registers or unregisters a class to the GxWMSLayerPropertiesPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxWMSLayerPropertiesPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxWMSLayerPropertiesPage : CatReg
  {

    /// <summary>Registers a class to the GxWMSLayerPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FA6CE80E-6322-44CB-82B1-3599DFF7EC61}");}

    /// <summary>Unregisters a class from the GxWMSLayerPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FA6CE80E-6322-44CB-82B1-3599DFF7EC61}");}
  }

  /// <summary>Registers or unregisters a class to the GxWMSMapPropertiesPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxWMSMapPropertiesPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxWMSMapPropertiesPage : CatReg
  {

    /// <summary>Registers a class to the GxWMSMapPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{05B8A7E8-994E-434E-97D9-51FC172C11A6}");}

    /// <summary>Unregisters a class from the GxWMSMapPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{05B8A7E8-994E-434E-97D9-51FC172C11A6}");}
  }

  /// <summary>Registers or unregisters a class to the GxWMTSServicePropertiesPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxWMTSServicePropertiesPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxWMTSServicePropertiesPage : CatReg
  {

    /// <summary>Registers a class to the GxWMTSServicePropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1E292BD5-0C68-458F-ACB6-2F8EFD0D9330}");}

    /// <summary>Unregisters a class from the GxWMTSServicePropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1E292BD5-0C68-458F-ACB6-2F8EFD0D9330}");}
  }

  /// <summary>Registers or unregisters a class to the GxWorkspaceDatabaseContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxWorkspaceDatabaseContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxWorkspaceDatabaseContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxWorkspaceDatabaseContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3C935660-D332-4A0C-A333-8D3C55461D35}");}

    /// <summary>Unregisters a class from the GxWorkspaceDatabaseContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3C935660-D332-4A0C-A333-8D3C55461D35}");}
  }

  /// <summary>Registers or unregisters a class to the GxXMLDocumentContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the GxXMLDocumentContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class GxXMLDocumentContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the GxXMLDocumentContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E18C85DE-F362-4985-8916-ADBA39A5A50D}");}

    /// <summary>Unregisters a class from the GxXMLDocumentContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E18C85DE-F362-4985-8916-ADBA39A5A50D}");}
  }

  /// <summary>Registers or unregisters a class to the HatchExpressionParsers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the HatchExpressionParsers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class HatchExpressionParsers : CatReg
  {

    /// <summary>Registers a class to the HatchExpressionParsers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AD1E8900-67E4-0E6B-FF78-56F38ABB3DF1}");}

    /// <summary>Unregisters a class from the HatchExpressionParsers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AD1E8900-67E4-0E6B-FF78-56F38ABB3DF1}");}
  }

  /// <summary>Registers or unregisters a class to the HelpMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the HelpMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class HelpMenuCommands : CatReg
  {

    /// <summary>Registers a class to the HelpMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{04BEAF7C-7D98-4259-8E68-20F9957E2329}");}

    /// <summary>Unregisters a class from the HelpMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{04BEAF7C-7D98-4259-8E68-20F9957E2329}");}
  }

  /// <summary>Registers or unregisters a class to the HotLinkExpressionParsers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the HotLinkExpressionParsers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class HotLinkExpressionParsers : CatReg
  {

    /// <summary>Registers a class to the HotLinkExpressionParsers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{529C0311-23F2-4D1A-8883-4B4C8C940209}");}

    /// <summary>Unregisters a class from the HotLinkExpressionParsers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{529C0311-23F2-4D1A-8883-4B4C8C940209}");}
  }

  /// <summary>Registers or unregisters a class to the IdentifyObj component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the IdentifyObj class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class IdentifyObj : CatReg
  {

    /// <summary>Registers a class to the IdentifyObj component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{997E7AC0-D353-11D2-8CD0-00C04F5B951E}");}

    /// <summary>Unregisters a class from the IdentifyObj component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{997E7AC0-D353-11D2-8CD0-00C04F5B951E}");}
  }

  /// <summary>Registers or unregisters a class to the ImageServerDatasetAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ImageServerDatasetAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ImageServerDatasetAnalyzers : CatReg
  {

    /// <summary>Registers a class to the ImageServerDatasetAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{19791BE9-DAE7-43ED-BE4F-BA772E45E797}");}

    /// <summary>Unregisters a class from the ImageServerDatasetAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{19791BE9-DAE7-43ED-BE4F-BA772E45E797}");}
  }

  /// <summary>Registers or unregisters a class to the ImageServerLayerAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ImageServerLayerAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ImageServerLayerAnalyzers : CatReg
  {

    /// <summary>Registers a class to the ImageServerLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BC08D8D4-87DF-4BAB-B3A3-87020C75472E}");}

    /// <summary>Unregisters a class from the ImageServerLayerAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BC08D8D4-87DF-4BAB-B3A3-87020C75472E}");}
  }

  /// <summary>Registers or unregisters a class to the ImageSettingsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ImageSettingsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ImageSettingsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ImageSettingsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CD4591EF-9EDE-4364-8F0E-CE0D7E6EC154}");}

    /// <summary>Unregisters a class from the ImageSettingsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CD4591EF-9EDE-4364-8F0E-CE0D7E6EC154}");}
  }

  /// <summary>Registers or unregisters a class to the IMSMetadataServicePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the IMSMetadataServicePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class IMSMetadataServicePropertyPages : CatReg
  {

    /// <summary>Registers a class to the IMSMetadataServicePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{079E9B6C-DA59-44EB-B129-E013139D3812}");}

    /// <summary>Unregisters a class from the IMSMetadataServicePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{079E9B6C-DA59-44EB-B129-E013139D3812}");}
  }

  /// <summary>Registers or unregisters a class to the IndexSearchOptionPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the IndexSearchOptionPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class IndexSearchOptionPages : CatReg
  {

    /// <summary>Registers a class to the IndexSearchOptionPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6F9EF4E0-563E-4596-8471-B0623577A479}");}

    /// <summary>Unregisters a class from the IndexSearchOptionPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6F9EF4E0-563E-4596-8471-B0623577A479}");}
  }

  /// <summary>Registers or unregisters a class to the InfoTablePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the InfoTablePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class InfoTablePropertyPages : CatReg
  {

    /// <summary>Registers a class to the InfoTablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5F7BBE85-E6EC-11D2-9F30-00C04F79927C}");}

    /// <summary>Unregisters a class from the InfoTablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5F7BBE85-E6EC-11D2-9F30-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the LabelStylePages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LabelStylePages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LabelStylePages : CatReg
  {

    /// <summary>Registers a class to the LabelStylePages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4C90DE7D-CB77-11D2-9F34-00C04F6BC6A5}");}

    /// <summary>Unregisters a class from the LabelStylePages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4C90DE7D-CB77-11D2-9F34-00C04F6BC6A5}");}
  }

  /// <summary>Registers or unregisters a class to the LabelStyleSelectors component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LabelStyleSelectors class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LabelStyleSelectors : CatReg
  {

    /// <summary>Registers a class to the LabelStyleSelectors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9E1FF0EB-BE15-4C55-B2CB-F96B73D1D905}");}

    /// <summary>Unregisters a class from the LabelStyleSelectors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9E1FF0EB-BE15-4C55-B2CB-F96B73D1D905}");}
  }

  /// <summary>Registers or unregisters a class to the LasDatasetPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LasDatasetPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LasDatasetPropertyPages : CatReg
  {

    /// <summary>Registers a class to the LasDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B4D464F4-3BB3-4F75-994C-B9E9C8B55346}");}

    /// <summary>Unregisters a class from the LasDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B4D464F4-3BB3-4F75-994C-B9E9C8B55346}");}
  }

  /// <summary>Registers or unregisters a class to the LasDatasetRendererPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LasDatasetRendererPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LasDatasetRendererPropertyPages : CatReg
  {

    /// <summary>Registers a class to the LasDatasetRendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{653D2F35-FA61-4479-926D-DFB1CC3A0602}");}

    /// <summary>Unregisters a class from the LasDatasetRendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{653D2F35-FA61-4479-926D-DFB1CC3A0602}");}
  }

  /// <summary>Registers or unregisters a class to the LayerDrawingDescriptionFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LayerDrawingDescriptionFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LayerDrawingDescriptionFactory : CatReg
  {

    /// <summary>Registers a class to the LayerDrawingDescriptionFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4F3A55E3-26DC-4DE0-8D47-B97C7D44F160}");}

    /// <summary>Unregisters a class from the LayerDrawingDescriptionFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4F3A55E3-26DC-4DE0-8D47-B97C7D44F160}");}
  }

  /// <summary>Registers or unregisters a class to the LayerFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LayerFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LayerFactory : CatReg
  {

    /// <summary>Registers a class to the LayerFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{34C20001-4D3C-11D0-92D8-00805F7C28B0}");}

    /// <summary>Unregisters a class from the LayerFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{34C20001-4D3C-11D0-92D8-00805F7C28B0}");}
  }

  /// <summary>Registers or unregisters a class to the LayerFactoryExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LayerFactoryExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LayerFactoryExtensions : CatReg
  {

    /// <summary>Registers a class to the LayerFactoryExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{90918879-5056-4E08-A3F1-D13590B2D15E}");}

    /// <summary>Unregisters a class from the LayerFactoryExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{90918879-5056-4E08-A3F1-D13590B2D15E}");}
  }

  /// <summary>Registers or unregisters a class to the LayerLabelsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LayerLabelsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LayerLabelsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the LayerLabelsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D80B7114-739C-4ECB-AD06-4DF67C0E6596}");}

    /// <summary>Unregisters a class from the LayerLabelsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D80B7114-739C-4ECB-AD06-4DF67C0E6596}");}
  }

  /// <summary>Registers or unregisters a class to the LayerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LayerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LayerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the LayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1476C782-6F57-11D2-A2C6-080009B6F22B}");}

    /// <summary>Unregisters a class from the LayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1476C782-6F57-11D2-A2C6-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the LayerPropertySheet component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LayerPropertySheet class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LayerPropertySheet : CatReg
  {

    /// <summary>Registers a class to the LayerPropertySheet component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DC70783B-5CE1-11D0-92DA-00805F7C28B0}");}

    /// <summary>Unregisters a class from the LayerPropertySheet component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DC70783B-5CE1-11D0-92DA-00805F7C28B0}");}
  }

  /// <summary>Registers or unregisters a class to the LegendItemPropSheets component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LegendItemPropSheets class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LegendItemPropSheets : CatReg
  {

    /// <summary>Registers a class to the LegendItemPropSheets component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4E91E870-4C86-11D1-880B-080009EC732A}");}

    /// <summary>Unregisters a class from the LegendItemPropSheets component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4E91E870-4C86-11D1-880B-080009EC732A}");}
  }

  /// <summary>Registers or unregisters a class to the LegendItems component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LegendItems class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LegendItems : CatReg
  {

    /// <summary>Registers a class to the LegendItems component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4E91E86F-4C86-11D1-880B-080009EC732A}");}

    /// <summary>Unregisters a class from the LegendItems component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4E91E86F-4C86-11D1-880B-080009EC732A}");}
  }

  /// <summary>Registers or unregisters a class to the LegendSymbolEditors component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LegendSymbolEditors class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LegendSymbolEditors : CatReg
  {

    /// <summary>Registers a class to the LegendSymbolEditors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9C275BE0-2A66-11D3-80E3-0080C79F0371}");}

    /// <summary>Unregisters a class from the LegendSymbolEditors component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9C275BE0-2A66-11D3-80E3-0080C79F0371}");}
  }

  /// <summary>Registers or unregisters a class to the LineCoveredByLineClassErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineCoveredByLineClassErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineCoveredByLineClassErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineCoveredByLineClassErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3B882828-5F84-4AE1-9F46-9BBF8E877679}");}

    /// <summary>Unregisters a class from the LineCoveredByLineClassErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3B882828-5F84-4AE1-9F46-9BBF8E877679}");}
  }

  /// <summary>Registers or unregisters a class to the LineDangleErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineDangleErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineDangleErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineDangleErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D98A1992-623A-49B6-9DB3-6CEC4BD1A49C}");}

    /// <summary>Unregisters a class from the LineDangleErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D98A1992-623A-49B6-9DB3-6CEC4BD1A49C}");}
  }

  /// <summary>Registers or unregisters a class to the LineDecorationElement component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineDecorationElement class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineDecorationElement : CatReg
  {

    /// <summary>Registers a class to the LineDecorationElement component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5673B810-2B1F-11D3-80E5-0080C79F0371}");}

    /// <summary>Unregisters a class from the LineDecorationElement component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5673B810-2B1F-11D3-80E5-0080C79F0371}");}
  }

  /// <summary>Registers or unregisters a class to the LineInsideAreaErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineInsideAreaErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineInsideAreaErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineInsideAreaErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BE3CD279-E9B2-4ADD-B1E9-8A71298B567E}");}

    /// <summary>Unregisters a class from the LineInsideAreaErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BE3CD279-E9B2-4ADD-B1E9-8A71298B567E}");}
  }

  /// <summary>Registers or unregisters a class to the LineIntersectionErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineIntersectionErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineIntersectionErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineIntersectionErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{94822460-BACD-493C-9398-9BD9EA7D8FC7}");}

    /// <summary>Unregisters a class from the LineIntersectionErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{94822460-BACD-493C-9398-9BD9EA7D8FC7}");}
  }

  /// <summary>Registers or unregisters a class to the LineIntersectionInteriorTouchErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineIntersectionInteriorTouchErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineIntersectionInteriorTouchErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineIntersectionInteriorTouchErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{58B3DD4C-8B9F-4CB7-B997-90AA4DF3989D}");}

    /// <summary>Unregisters a class from the LineIntersectionInteriorTouchErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{58B3DD4C-8B9F-4CB7-B997-90AA4DF3989D}");}
  }

  /// <summary>Registers or unregisters a class to the LineMultipartErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineMultipartErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineMultipartErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineMultipartErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{464DA432-E5F1-47B3-A3BA-5981F0AAA4AA}");}

    /// <summary>Unregisters a class from the LineMultipartErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{464DA432-E5F1-47B3-A3BA-5981F0AAA4AA}");}
  }

  /// <summary>Registers or unregisters a class to the LineOverlapErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineOverlapErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineOverlapErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineOverlapErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{88011378-E9FE-4F21-A5FE-209C49EEB4DF}");}

    /// <summary>Unregisters a class from the LineOverlapErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{88011378-E9FE-4F21-A5FE-209C49EEB4DF}");}
  }

  /// <summary>Registers or unregisters a class to the LinePatches component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LinePatches class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LinePatches : CatReg
  {

    /// <summary>Registers a class to the LinePatches component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F21E3E7C-E3BA-11D2-B868-00600802E603}");}

    /// <summary>Unregisters a class from the LinePatches component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F21E3E7C-E3BA-11D2-B868-00600802E603}");}
  }

  /// <summary>Registers or unregisters a class to the LinePseudoErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LinePseudoErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LinePseudoErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LinePseudoErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1C65B1FA-2CAE-4850-81C8-F4B119B738B2}");}

    /// <summary>Unregisters a class from the LinePseudoErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1C65B1FA-2CAE-4850-81C8-F4B119B738B2}");}
  }

  /// <summary>Registers or unregisters a class to the LineSelfIntersectErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineSelfIntersectErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineSelfIntersectErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineSelfIntersectErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E71D7DB1-84AD-4C58-9AC1-FD440BF190C5}");}

    /// <summary>Unregisters a class from the LineSelfIntersectErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E71D7DB1-84AD-4C58-9AC1-FD440BF190C5}");}
  }

  /// <summary>Registers or unregisters a class to the LineSelfOverlapErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineSelfOverlapErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineSelfOverlapErrorCommands : CatReg
  {

    /// <summary>Registers a class to the LineSelfOverlapErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CE81C0A2-0A70-4F2C-9096-8E9DCB753400}");}

    /// <summary>Unregisters a class from the LineSelfOverlapErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CE81C0A2-0A70-4F2C-9096-8E9DCB753400}");}
  }

  /// <summary>Registers or unregisters a class to the LineSymbol component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LineSymbol class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LineSymbol : CatReg
  {

    /// <summary>Registers a class to the LineSymbol component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5424FB00-5713-11D2-97E5-0080C7E04196}");}

    /// <summary>Unregisters a class from the LineSymbol component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5424FB00-5713-11D2-97E5-0080C7E04196}");}
  }

  /// <summary>Registers or unregisters a class to the LocatorWorkspaces component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the LocatorWorkspaces class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class LocatorWorkspaces : CatReg
  {

    /// <summary>Registers a class to the LocatorWorkspaces component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DD0E0458-59CD-4289-8E8A-11B28D9B2B9B}");}

    /// <summary>Unregisters a class from the LocatorWorkspaces component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DD0E0458-59CD-4289-8E8A-11B28D9B2B9B}");}
  }

  /// <summary>Registers or unregisters a class to the MapAnimationTypes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MapAnimationTypes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MapAnimationTypes : CatReg
  {

    /// <summary>Registers a class to the MapAnimationTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{310C13BB-2813-4F9A-B202-4F7C23829F92}");}

    /// <summary>Unregisters a class from the MapAnimationTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{310C13BB-2813-4F9A-B202-4F7C23829F92}");}
  }

  /// <summary>Registers or unregisters a class to the MapDocumentPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MapDocumentPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MapDocumentPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MapDocumentPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BC57B66A-41FC-4806-835A-DC6E520F765D}");}

    /// <summary>Unregisters a class from the MapDocumentPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BC57B66A-41FC-4806-835A-DC6E520F765D}");}
  }

  /// <summary>Registers or unregisters a class to the MapGridBorders component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MapGridBorders class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MapGridBorders : CatReg
  {

    /// <summary>Registers a class to the MapGridBorders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8AF09A6E-A0DD-11D2-AE7F-080009EC732A}");}

    /// <summary>Unregisters a class from the MapGridBorders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8AF09A6E-A0DD-11D2-AE7F-080009EC732A}");}
  }

  /// <summary>Registers or unregisters a class to the MapGridFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MapGridFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MapGridFactory : CatReg
  {

    /// <summary>Registers a class to the MapGridFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A0C55AF7-F9D5-11D1-AA8E-000000000000}");}

    /// <summary>Unregisters a class from the MapGridFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A0C55AF7-F9D5-11D1-AA8E-000000000000}");}
  }

  /// <summary>Registers or unregisters a class to the MapGridPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MapGridPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MapGridPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MapGridPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{452A7917-1B8E-11D3-9F92-00C04F6BC78E}");}

    /// <summary>Unregisters a class from the MapGridPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{452A7917-1B8E-11D3-9F92-00C04F6BC78E}");}
  }

  /// <summary>Registers or unregisters a class to the MaplexAnnotationPlacementPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MaplexAnnotationPlacementPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MaplexAnnotationPlacementPages : CatReg
  {

    /// <summary>Registers a class to the MaplexAnnotationPlacementPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{20664808-6EC9-11D2-A2C6-080009B6F22B}");}

    /// <summary>Unregisters a class from the MaplexAnnotationPlacementPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{20664808-6EC9-11D2-A2C6-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the MaplexLabelStylePages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MaplexLabelStylePages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MaplexLabelStylePages : CatReg
  {

    /// <summary>Registers a class to the MaplexLabelStylePages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{20664808-6EC9-12D2-A3C6-050009B7FA2B}");}

    /// <summary>Unregisters a class from the MaplexLabelStylePages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{20664808-6EC9-12D2-A3C6-050009B7FA2B}");}
  }

  /// <summary>Registers or unregisters a class to the MapPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MapPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MapPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MapPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AE76C8D2-A58A-11D2-A2FE-080009B6F22B}");}

    /// <summary>Unregisters a class from the MapPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AE76C8D2-A58A-11D2-A2FE-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the MapScalePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MapScalePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MapScalePropertyPages : CatReg
  {

    /// <summary>Registers a class to the MapScalePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{523318B3-C40C-4D7C-9C6B-34684742BD18}");}

    /// <summary>Unregisters a class from the MapScalePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{523318B3-C40C-4D7C-9C6B-34684742BD18}");}
  }

  /// <summary>Registers or unregisters a class to the MarkerPlacement component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MarkerPlacement class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MarkerPlacement : CatReg
  {

    /// <summary>Registers a class to the MarkerPlacement component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B6BB782B-E479-4D59-B152-51466ADF7D50}");}

    /// <summary>Unregisters a class from the MarkerPlacement component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B6BB782B-E479-4D59-B152-51466ADF7D50}");}
  }

  /// <summary>Registers or unregisters a class to the MarkerSymbol component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MarkerSymbol class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MarkerSymbol : CatReg
  {

    /// <summary>Registers a class to the MarkerSymbol component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5424FB01-5713-11D2-97E5-0080C7E04196}");}

    /// <summary>Unregisters a class from the MarkerSymbol component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5424FB01-5713-11D2-97E5-0080C7E04196}");}
  }

  /// <summary>Registers or unregisters a class to the MBDerivedGeoDatasetProp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MBDerivedGeoDatasetProp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MBDerivedGeoDatasetProp : CatReg
  {

    /// <summary>Registers a class to the MBDerivedGeoDatasetProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7386B03-775E-11D3-9F54-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the MBDerivedGeoDatasetProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7386B03-775E-11D3-9F54-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the MBGeoDatasetProp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MBGeoDatasetProp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MBGeoDatasetProp : CatReg
  {

    /// <summary>Registers a class to the MBGeoDatasetProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7386B01-775E-11D3-9F54-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the MBGeoDatasetProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7386B01-775E-11D3-9F54-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the MBGeoOperationProp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MBGeoOperationProp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MBGeoOperationProp : CatReg
  {

    /// <summary>Registers a class to the MBGeoOperationProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7386B05-775E-11D3-9F54-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the MBGeoOperationProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7386B05-775E-11D3-9F54-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the MBLayerProp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MBLayerProp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MBLayerProp : CatReg
  {

    /// <summary>Registers a class to the MBLayerProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7386B02-775E-11D3-9F54-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the MBLayerProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7386B02-775E-11D3-9F54-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the MBMethodProp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MBMethodProp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MBMethodProp : CatReg
  {

    /// <summary>Registers a class to the MBMethodProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7386B06-775E-11D3-9F54-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the MBMethodProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7386B06-775E-11D3-9F54-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the MBProcessProp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MBProcessProp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MBProcessProp : CatReg
  {

    /// <summary>Registers a class to the MBProcessProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7386B07-775E-11D3-9F54-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the MBProcessProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7386B07-775E-11D3-9F54-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the MBTableProp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MBTableProp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MBTableProp : CatReg
  {

    /// <summary>Registers a class to the MBTableProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7386B04-775E-11D3-9F54-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the MBTableProp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7386B04-775E-11D3-9F54-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the MdDiagramPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MdDiagramPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MdDiagramPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MdDiagramPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EE49CC60-5269-49BD-A42C-957297C8EE47}");}

    /// <summary>Unregisters a class from the MdDiagramPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EE49CC60-5269-49BD-A42C-957297C8EE47}");}
  }

  /// <summary>Registers or unregisters a class to the MdElementMetadataPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MdElementMetadataPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MdElementMetadataPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MdElementMetadataPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{1CC0FC51-B1E0-4E78-95AC-C2F699890C43}");}

    /// <summary>Unregisters a class from the MdElementMetadataPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{1CC0FC51-B1E0-4E78-95AC-C2F699890C43}");}
  }

  /// <summary>Registers or unregisters a class to the MdElementPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MdElementPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MdElementPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MdElementPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DDB9EA8D-8D12-42A4-B3D4-C3E9D371CAD9}");}

    /// <summary>Unregisters a class from the MdElementPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DDB9EA8D-8D12-42A4-B3D4-C3E9D371CAD9}");}
  }

  /// <summary>Registers or unregisters a class to the MdProcessPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MdProcessPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MdProcessPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MdProcessPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{303635ED-41E4-4259-AF51-6C00DF5B30DB}");}

    /// <summary>Unregisters a class from the MdProcessPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{303635ED-41E4-4259-AF51-6C00DF5B30DB}");}
  }

  /// <summary>Registers or unregisters a class to the MetadataEditor component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MetadataEditor class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MetadataEditor : CatReg
  {

    /// <summary>Registers a class to the MetadataEditor component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7AD0DA0A-0D4A-11D3-A626-0008C7D3AE50}");}

    /// <summary>Unregisters a class from the MetadataEditor component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7AD0DA0A-0D4A-11D3-A626-0008C7D3AE50}");}
  }

  /// <summary>Registers or unregisters a class to the MetadataEditorPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MetadataEditorPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MetadataEditorPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MetadataEditorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5907D721-04C9-11D3-83FF-00C04F8ED211}");}

    /// <summary>Unregisters a class from the MetadataEditorPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5907D721-04C9-11D3-83FF-00C04F8ED211}");}
  }

  /// <summary>Registers or unregisters a class to the MetadataSynchronizers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MetadataSynchronizers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MetadataSynchronizers : CatReg
  {

    /// <summary>Registers a class to the MetadataSynchronizers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A802F1A4-E795-4169-997C-6B8FE2F53F98}");}

    /// <summary>Unregisters a class from the MetadataSynchronizers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A802F1A4-E795-4169-997C-6B8FE2F53F98}");}
  }

  /// <summary>Registers or unregisters a class to the ModelScriptConverters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ModelScriptConverters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ModelScriptConverters : CatReg
  {

    /// <summary>Registers a class to the ModelScriptConverters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0E771440-2E3B-4D88-B0BD-51F9684DAF9E}");}

    /// <summary>Unregisters a class from the ModelScriptConverters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0E771440-2E3B-4D88-B0BD-51F9684DAF9E}");}
  }

  /// <summary>Registers or unregisters a class to the MosaicDatasetEnhanceMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MosaicDatasetEnhanceMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MosaicDatasetEnhanceMenuCommands : CatReg
  {

    /// <summary>Registers a class to the MosaicDatasetEnhanceMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CBA9CDA8-0D3C-471F-ACFB-104BE8A22F29}");}

    /// <summary>Unregisters a class from the MosaicDatasetEnhanceMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CBA9CDA8-0D3C-471F-ACFB-104BE8A22F29}");}
  }

  /// <summary>Registers or unregisters a class to the MosaicDatasetExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MosaicDatasetExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MosaicDatasetExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the MosaicDatasetExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A95856C5-25D6-416C-AB2B-CD84E1A80992}");}

    /// <summary>Unregisters a class from the MosaicDatasetExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A95856C5-25D6-416C-AB2B-CD84E1A80992}");}
  }

  /// <summary>Registers or unregisters a class to the MosaicDatasetModifyMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MosaicDatasetModifyMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MosaicDatasetModifyMenuCommands : CatReg
  {

    /// <summary>Registers a class to the MosaicDatasetModifyMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EA8DE9CF-41B5-424A-BD34-F16C20E0B4B1}");}

    /// <summary>Unregisters a class from the MosaicDatasetModifyMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EA8DE9CF-41B5-424A-BD34-F16C20E0B4B1}");}
  }

  /// <summary>Registers or unregisters a class to the MosaicDatasetOptimizeMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MosaicDatasetOptimizeMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MosaicDatasetOptimizeMenuCommands : CatReg
  {

    /// <summary>Registers a class to the MosaicDatasetOptimizeMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3FE2924D-5960-4AF1-8719-3837E5B59DB4}");}

    /// <summary>Unregisters a class from the MosaicDatasetOptimizeMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3FE2924D-5960-4AF1-8719-3837E5B59DB4}");}
  }

  /// <summary>Registers or unregisters a class to the MosaicDatasetRemoveMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MosaicDatasetRemoveMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MosaicDatasetRemoveMenuCommands : CatReg
  {

    /// <summary>Registers a class to the MosaicDatasetRemoveMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A95856C5-25D6-416C-AB2B-CD84E1A80993}");}

    /// <summary>Unregisters a class from the MosaicDatasetRemoveMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A95856C5-25D6-416C-AB2B-CD84E1A80993}");}
  }

  /// <summary>Registers or unregisters a class to the MosaicLayerPreviewPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MosaicLayerPreviewPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MosaicLayerPreviewPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MosaicLayerPreviewPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{16D9E51E-5537-4AB0-B3F0-0494F6AF8904}");}

    /// <summary>Unregisters a class from the MosaicLayerPreviewPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{16D9E51E-5537-4AB0-B3F0-0494F6AF8904}");}
  }

  /// <summary>Registers or unregisters a class to the MultiGenReplicaPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MultiGenReplicaPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MultiGenReplicaPropertyPages : CatReg
  {

    /// <summary>Registers a class to the MultiGenReplicaPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AFFBB220-DC14-475B-8FD1-F75B5DBAB8B6}");}

    /// <summary>Unregisters a class from the MultiGenReplicaPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AFFBB220-DC14-475B-8FD1-F75B5DBAB8B6}");}
  }

  /// <summary>Registers or unregisters a class to the MxCommandBars component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxCommandBars class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxCommandBars : CatReg
  {

    /// <summary>Registers a class to the MxCommandBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B56A7C4A-83D4-11D2-A2E9-080009B6F22B}");}

    /// <summary>Unregisters a class from the MxCommandBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B56A7C4A-83D4-11D2-A2E9-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the MxCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxCommands : CatReg
  {

    /// <summary>Registers a class to the MxCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B56A7C42-83D4-11D2-A2E9-080009B6F22B}");}

    /// <summary>Unregisters a class from the MxCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B56A7C42-83D4-11D2-A2E9-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the MxDDECommandHandler component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxDDECommandHandler class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxDDECommandHandler : CatReg
  {

    /// <summary>Registers a class to the MxDDECommandHandler component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F440A933-565C-447C-8C56-28BB0404E5B9}");}

    /// <summary>Unregisters a class from the MxDDECommandHandler component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F440A933-565C-447C-8C56-28BB0404E5B9}");}
  }

  /// <summary>Registers or unregisters a class to the MxDockableWindows component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxDockableWindows class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxDockableWindows : CatReg
  {

    /// <summary>Registers a class to the MxDockableWindows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{117623B5-F9D1-11D3-A67F-0008C7DF97B9}");}

    /// <summary>Unregisters a class from the MxDockableWindows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{117623B5-F9D1-11D3-A67F-0008C7DF97B9}");}
  }

  /// <summary>Registers or unregisters a class to the MxDocumentDropTarget component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxDocumentDropTarget class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxDocumentDropTarget : CatReg
  {

    /// <summary>Registers a class to the MxDocumentDropTarget component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9168AC07-5DBE-11D4-A689-0008C7DF88DB}");}

    /// <summary>Unregisters a class from the MxDocumentDropTarget component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9168AC07-5DBE-11D4-A689-0008C7DF88DB}");}
  }

  /// <summary>Registers or unregisters a class to the MxExtension component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxExtension class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxExtension : CatReg
  {

    /// <summary>Registers a class to the MxExtension component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B56A7C45-83D4-11D2-A2E9-080009B6F22B}");}

    /// <summary>Unregisters a class from the MxExtension component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B56A7C45-83D4-11D2-A2E9-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the MxExtensionJIT component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxExtensionJIT class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxExtensionJIT : CatReg
  {

    /// <summary>Registers a class to the MxExtensionJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B8C1C6CD-BE34-4EED-BAE9-8584F7A61B07}");}

    /// <summary>Unregisters a class from the MxExtensionJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B8C1C6CD-BE34-4EED-BAE9-8584F7A61B07}");}
  }

  /// <summary>Registers or unregisters a class to the MxFileMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxFileMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxFileMenuCommands : CatReg
  {

    /// <summary>Registers a class to the MxFileMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F8FC396D-5BA0-44A8-98C4-96C70C5312DE}");}

    /// <summary>Unregisters a class from the MxFileMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F8FC396D-5BA0-44A8-98C4-96C70C5312DE}");}
  }

  /// <summary>Registers or unregisters a class to the MxFileMenuDefs component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxFileMenuDefs class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxFileMenuDefs : CatReg
  {

    /// <summary>Registers a class to the MxFileMenuDefs component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6F400F1B-1B8F-4469-9581-A0A3826B9FD5}");}

    /// <summary>Unregisters a class from the MxFileMenuDefs component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6F400F1B-1B8F-4469-9581-A0A3826B9FD5}");}
  }

  /// <summary>Registers or unregisters a class to the MxFinders component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxFinders class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxFinders : CatReg
  {

    /// <summary>Registers a class to the MxFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8803C8EF-75FE-11D3-A6A6-0008C7D3AE50}");}

    /// <summary>Unregisters a class from the MxFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8803C8EF-75FE-11D3-A6A6-0008C7D3AE50}");}
  }

  /// <summary>Registers or unregisters a class to the MxInsetWindowPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxInsetWindowPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxInsetWindowPages : CatReg
  {

    /// <summary>Registers a class to the MxInsetWindowPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{67713804-1368-4C15-A064-639396316EC8}");}

    /// <summary>Unregisters a class from the MxInsetWindowPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{67713804-1368-4C15-A064-639396316EC8}");}
  }

  /// <summary>Registers or unregisters a class to the MxPalettes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxPalettes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxPalettes : CatReg
  {

    /// <summary>Registers a class to the MxPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B56A7C48-83D4-11D2-A2E9-080009B6F22B}");}

    /// <summary>Unregisters a class from the MxPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B56A7C48-83D4-11D2-A2E9-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the MxToolMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxToolMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxToolMenuCommands : CatReg
  {

    /// <summary>Registers a class to the MxToolMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6B1DF87B-DEC8-49B0-884F-345FE2EB1274}");}

    /// <summary>Unregisters a class from the MxToolMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6B1DF87B-DEC8-49B0-884F-345FE2EB1274}");}
  }

  /// <summary>Registers or unregisters a class to the MxViewCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the MxViewCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class MxViewCommands : CatReg
  {

    /// <summary>Registers a class to the MxViewCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B56A7C43-83D4-11D2-A2E9-080009B6F22B}");}

    /// <summary>Unregisters a class from the MxViewCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B56A7C43-83D4-11D2-A2E9-080009B6F22B}");}
  }

  /// <summary>Registers or unregisters a class to the NameStringParser component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NameStringParser class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NameStringParser : CatReg
  {

    /// <summary>Registers a class to the NameStringParser component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7BF26B1F-C776-11D2-9F24-00C04F6BC69E}");}

    /// <summary>Unregisters a class from the NameStringParser component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7BF26B1F-C776-11D2-9F24-00C04F6BC69E}");}
  }

  /// <summary>Registers or unregisters a class to the NativeTypes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NativeTypes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NativeTypes : CatReg
  {

    /// <summary>Registers a class to the NativeTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D80D64ED-0B0F-4C45-B68C-F71F1C310353}");}

    /// <summary>Unregisters a class from the NativeTypes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D80D64ED-0B0F-4C45-B68C-F71F1C310353}");}
  }

  /// <summary>Registers or unregisters a class to the Navigate3DInputDevices component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the Navigate3DInputDevices class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class Navigate3DInputDevices : CatReg
  {

    /// <summary>Registers a class to the Navigate3DInputDevices component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{73BEB59F-8169-44D9-AD01-84A6EAFD6B49}");}

    /// <summary>Unregisters a class from the Navigate3DInputDevices component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{73BEB59F-8169-44D9-AD01-84A6EAFD6B49}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystAgent component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystAgent class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystAgent : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystAgent component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{14A4B9CF-BEFA-475A-BAB2-11403ACF37A6}");}

    /// <summary>Unregisters a class from the NetworkAnalystAgent component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{14A4B9CF-BEFA-475A-BAB2-11403ACF37A6}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystFinders component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystFinders class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystFinders : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{86A82C2B-D6B7-466F-8047-C6B232D8577E}");}

    /// <summary>Unregisters a class from the NetworkAnalystFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{86A82C2B-D6B7-466F-8047-C6B232D8577E}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystLocationOptionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystLocationOptionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystLocationOptionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystLocationOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{16558225-DCAE-489F-98AE-12119CAFE888}");}

    /// <summary>Unregisters a class from the NetworkAnalystLocationOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{16558225-DCAE-489F-98AE-12119CAFE888}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystOptionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystOptionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystOptionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{53A05670-1E0A-4765-A3D2-30A5051379AB}");}

    /// <summary>Unregisters a class from the NetworkAnalystOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{53A05670-1E0A-4765-A3D2-30A5051379AB}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystSolver component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystSolver class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystSolver : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystSolver component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EAE35861-A806-4100-A148-8E99F6E762B2}");}

    /// <summary>Unregisters a class from the NetworkAnalystSolver component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EAE35861-A806-4100-A148-8E99F6E762B2}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystSymbolizer component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystSymbolizer class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystSymbolizer : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystSymbolizer component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{22DE1F4B-149D-4FC5-8FC3-6BBE5483F083}");}

    /// <summary>Unregisters a class from the NetworkAnalystSymbolizer component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{22DE1F4B-149D-4FC5-8FC3-6BBE5483F083}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystWindowCategoryCommand component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystWindowCategoryCommand class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystWindowCategoryCommand : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystWindowCategoryCommand component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{37ECC184-D569-4D28-9636-D15A609F01AE}");}

    /// <summary>Unregisters a class from the NetworkAnalystWindowCategoryCommand component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{37ECC184-D569-4D28-9636-D15A609F01AE}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystWindowItemCategory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystWindowItemCategory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystWindowItemCategory : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystWindowItemCategory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{177F3D7A-E9D3-497F-94FA-E23CABCA555E}");}

    /// <summary>Unregisters a class from the NetworkAnalystWindowItemCategory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{177F3D7A-E9D3-497F-94FA-E23CABCA555E}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkAnalystWindowItemsCommand component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkAnalystWindowItemsCommand class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkAnalystWindowItemsCommand : CatReg
  {

    /// <summary>Registers a class to the NetworkAnalystWindowItemsCommand component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{595FF015-797F-4C32-A0EC-B20F1ABDB18E}");}

    /// <summary>Unregisters a class from the NetworkAnalystWindowItemsCommand component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{595FF015-797F-4C32-A0EC-B20F1ABDB18E}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkDirectionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkDirectionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkDirectionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the NetworkDirectionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E23FA50B-E545-49C1-9383-66A81D1435DA}");}

    /// <summary>Unregisters a class from the NetworkDirectionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E23FA50B-E545-49C1-9383-66A81D1435DA}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkEvaluatorEditor component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkEvaluatorEditor class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkEvaluatorEditor : CatReg
  {

    /// <summary>Registers a class to the NetworkEvaluatorEditor component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{013A2176-A747-41CE-BBDF-8DB1434EFB9E}");}

    /// <summary>Unregisters a class from the NetworkEvaluatorEditor component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{013A2176-A747-41CE-BBDF-8DB1434EFB9E}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkLayerSymbology component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkLayerSymbology class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkLayerSymbology : CatReg
  {

    /// <summary>Registers a class to the NetworkLayerSymbology component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3E7A486C-28C6-47ED-9F9F-AD77F7754D6D}");}

    /// <summary>Unregisters a class from the NetworkLayerSymbology component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3E7A486C-28C6-47ED-9F9F-AD77F7754D6D}");}
  }

  /// <summary>Registers or unregisters a class to the NetworkRendererPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NetworkRendererPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NetworkRendererPropertyPages : CatReg
  {

    /// <summary>Registers a class to the NetworkRendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6625CBA2-FF53-443E-A008-F3043082BA71}");}

    /// <summary>Unregisters a class from the NetworkRendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6625CBA2-FF53-443E-A008-F3043082BA71}");}
  }

  /// <summary>Registers or unregisters a class to the NotMaskableLayers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NotMaskableLayers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NotMaskableLayers : CatReg
  {

    /// <summary>Registers a class to the NotMaskableLayers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7D26C3DF-78CD-4D7C-A96A-FC75CE9F6B7C}");}

    /// <summary>Unregisters a class from the NotMaskableLayers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7D26C3DF-78CD-4D7C-A96A-FC75CE9F6B7C}");}
  }

  /// <summary>Registers or unregisters a class to the NumberFormatPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the NumberFormatPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class NumberFormatPropertyPages : CatReg
  {

    /// <summary>Registers a class to the NumberFormatPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{88002C0B-939A-11D2-AE73-080009EC732A}");}

    /// <summary>Unregisters a class from the NumberFormatPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{88002C0B-939A-11D2-AE73-080009EC732A}");}
  }

  /// <summary>Registers or unregisters a class to the OptimizerComponentFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the OptimizerComponentFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class OptimizerComponentFactory : CatReg
  {

    /// <summary>Registers a class to the OptimizerComponentFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C1FF474E-4DDF-44DA-9E94-4B848F33B749}");}

    /// <summary>Unregisters a class from the OptimizerComponentFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C1FF474E-4DDF-44DA-9E94-4B848F33B749}");}
  }

  /// <summary>Registers or unregisters a class to the OptionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the OptionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class OptionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the OptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FB8C2199-9D0A-11D3-A645-0008C7DF8DE1}");}

    /// <summary>Unregisters a class from the OptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FB8C2199-9D0A-11D3-A645-0008C7DF8DE1}");}
  }

  /// <summary>Registers or unregisters a class to the OverposterPropertiesPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the OverposterPropertiesPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class OverposterPropertiesPages : CatReg
  {

    /// <summary>Registers a class to the OverposterPropertiesPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4D1F6762-971D-46EA-B4FB-65801E5A4EDD}");}

    /// <summary>Unregisters a class from the OverposterPropertiesPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4D1F6762-971D-46EA-B4FB-65801E5A4EDD}");}
  }

  /// <summary>Registers or unregisters a class to the Overposters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the Overposters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class Overposters : CatReg
  {

    /// <summary>Registers a class to the Overposters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{895F0E7F-7451-4F9E-ADAA-B56ABE81D5D3}");}

    /// <summary>Unregisters a class from the Overposters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{895F0E7F-7451-4F9E-ADAA-B56ABE81D5D3}");}
  }

  /// <summary>Registers or unregisters a class to the PageIndexPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PageIndexPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PageIndexPropertyPages : CatReg
  {

    /// <summary>Registers a class to the PageIndexPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{803F079E-C13A-4A93-BF58-F06F67FC2C5B}");}

    /// <summary>Unregisters a class from the PageIndexPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{803F079E-C13A-4A93-BF58-F06F67FC2C5B}");}
  }

  /// <summary>Registers or unregisters a class to the Pictures component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the Pictures class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class Pictures : CatReg
  {

    /// <summary>Registers a class to the Pictures component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{289C9956-C063-11D2-9F22-00C04F6BC8DD}");}

    /// <summary>Unregisters a class from the Pictures component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{289C9956-C063-11D2-9F22-00C04F6BC8DD}");}
  }

  /// <summary>Registers or unregisters a class to the PlugInWorkspaceFactoryHelpers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PlugInWorkspaceFactoryHelpers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PlugInWorkspaceFactoryHelpers : CatReg
  {

    /// <summary>Registers a class to the PlugInWorkspaceFactoryHelpers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{6871A79C-CD65-46F5-A7BB-88F97D0E2CDC}");}

    /// <summary>Unregisters a class from the PlugInWorkspaceFactoryHelpers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{6871A79C-CD65-46F5-A7BB-88F97D0E2CDC}");}
  }

  /// <summary>Registers or unregisters a class to the PointCoincideErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PointCoincideErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PointCoincideErrorCommands : CatReg
  {

    /// <summary>Registers a class to the PointCoincideErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C46AAB78-B77E-497A-B50D-2EE2619912BF}");}

    /// <summary>Unregisters a class from the PointCoincideErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C46AAB78-B77E-497A-B50D-2EE2619912BF}");}
  }

  /// <summary>Registers or unregisters a class to the PointCoveredByAreaBoundaryErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PointCoveredByAreaBoundaryErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PointCoveredByAreaBoundaryErrorCommands : CatReg
  {

    /// <summary>Registers a class to the PointCoveredByAreaBoundaryErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2AC04BF5-48A2-4D7C-A695-103198CB8133}");}

    /// <summary>Unregisters a class from the PointCoveredByAreaBoundaryErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2AC04BF5-48A2-4D7C-A695-103198CB8133}");}
  }

  /// <summary>Registers or unregisters a class to the PointCoveredByEndpointErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PointCoveredByEndpointErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PointCoveredByEndpointErrorCommands : CatReg
  {

    /// <summary>Registers a class to the PointCoveredByEndpointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{08B33C03-50D6-4C54-8EF8-E2F8A0D2C21D}");}

    /// <summary>Unregisters a class from the PointCoveredByEndpointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{08B33C03-50D6-4C54-8EF8-E2F8A0D2C21D}");}
  }

  /// <summary>Registers or unregisters a class to the PointCoveredByLineErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PointCoveredByLineErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PointCoveredByLineErrorCommands : CatReg
  {

    /// <summary>Registers a class to the PointCoveredByLineErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0D0B210D-ED73-4A45-A60D-D34D45776777}");}

    /// <summary>Unregisters a class from the PointCoveredByLineErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0D0B210D-ED73-4A45-A60D-D34D45776777}");}
  }

  /// <summary>Registers or unregisters a class to the PointDisjointErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PointDisjointErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PointDisjointErrorCommands : CatReg
  {

    /// <summary>Registers a class to the PointDisjointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D46118FD-82F6-42EC-B8CB-2B8DC3E47EB2}");}

    /// <summary>Unregisters a class from the PointDisjointErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D46118FD-82F6-42EC-B8CB-2B8DC3E47EB2}");}
  }

  /// <summary>Registers or unregisters a class to the PointInsideAreaErrorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PointInsideAreaErrorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PointInsideAreaErrorCommands : CatReg
  {

    /// <summary>Registers a class to the PointInsideAreaErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FFD26B46-C52E-4816-8756-4CDEEBC6EC58}");}

    /// <summary>Unregisters a class from the PointInsideAreaErrorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FFD26B46-C52E-4816-8756-4CDEEBC6EC58}");}
  }

  /// <summary>Registers or unregisters a class to the Pre70CoveragePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the Pre70CoveragePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class Pre70CoveragePropertyPages : CatReg
  {

    /// <summary>Registers a class to the Pre70CoveragePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C65A2BB7-32ED-11D3-9F33-00C04F79927C}");}

    /// <summary>Unregisters a class from the Pre70CoveragePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C65A2BB7-32ED-11D3-9F33-00C04F79927C}");}
  }

  /// <summary>Registers or unregisters a class to the PrinterDrivers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PrinterDrivers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PrinterDrivers : CatReg
  {

    /// <summary>Registers a class to the PrinterDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DF933391-7A7A-11D2-ACF9-0000F87808EE}");}

    /// <summary>Unregisters a class from the PrinterDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DF933391-7A7A-11D2-ACF9-0000F87808EE}");}
  }

  /// <summary>Registers or unregisters a class to the PrinterPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PrinterPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PrinterPropertyPages : CatReg
  {

    /// <summary>Registers a class to the PrinterPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9A797CC1-5E01-11D2-9181-0000F87808EE}");}

    /// <summary>Unregisters a class from the PrinterPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9A797CC1-5E01-11D2-9181-0000F87808EE}");}
  }

  /// <summary>Registers or unregisters a class to the ProjectedCoordSysPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ProjectedCoordSysPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ProjectedCoordSysPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ProjectedCoordSysPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7E9913E2-E22E-11D2-99C0-0000F80372B4}");}

    /// <summary>Unregisters a class from the ProjectedCoordSysPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7E9913E2-E22E-11D2-99C0-0000F80372B4}");}
  }

  /// <summary>Registers or unregisters a class to the PropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the PropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class PropertyPages : CatReg
  {

    /// <summary>Registers a class to the PropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C899AE27-E515-11D1-877C-0000F8751720}");}

    /// <summary>Unregisters a class from the PropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C899AE27-E515-11D1-877C-0000F8751720}");}
  }

  /// <summary>Registers or unregisters a class to the RasterAnalysis component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterAnalysis class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterAnalysis : CatReg
  {

    /// <summary>Registers a class to the RasterAnalysis component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{59CA6922-47FB-11D2-8D29-0000F8780535}");}

    /// <summary>Unregisters a class from the RasterAnalysis component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{59CA6922-47FB-11D2-8D29-0000F8780535}");}
  }

  /// <summary>Registers or unregisters a class to the RasterBandPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterBandPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterBandPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RasterBandPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DC942D39-E3A8-11D2-9F52-00C04F8ED21A}");}

    /// <summary>Unregisters a class from the RasterBandPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DC942D39-E3A8-11D2-9F52-00C04F8ED21A}");}
  }

  /// <summary>Registers or unregisters a class to the RasterCatalogExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterCatalogExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterCatalogExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the RasterCatalogExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{83D9148B-8E34-47DA-9C54-57436B6493DF}");}

    /// <summary>Unregisters a class from the RasterCatalogExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{83D9148B-8E34-47DA-9C54-57436B6493DF}");}
  }

  /// <summary>Registers or unregisters a class to the RasterCatalogLoadMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterCatalogLoadMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterCatalogLoadMenuCommands : CatReg
  {

    /// <summary>Registers a class to the RasterCatalogLoadMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{291D0CF0-8D47-452C-B6A9-5464C312B91D}");}

    /// <summary>Unregisters a class from the RasterCatalogLoadMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{291D0CF0-8D47-452C-B6A9-5464C312B91D}");}
  }

  /// <summary>Registers or unregisters a class to the RasterCatalogRendererPickers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterCatalogRendererPickers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterCatalogRendererPickers : CatReg
  {

    /// <summary>Registers a class to the RasterCatalogRendererPickers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D7A4486F-C20B-4625-8703-08AEFB1D0839}");}

    /// <summary>Unregisters a class from the RasterCatalogRendererPickers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D7A4486F-C20B-4625-8703-08AEFB1D0839}");}
  }

  /// <summary>Registers or unregisters a class to the RasterCatalogRenderersPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterCatalogRenderersPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterCatalogRenderersPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RasterCatalogRenderersPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3BCD05ED-97E1-46DF-8034-533C84685EA2}");}

    /// <summary>Unregisters a class from the RasterCatalogRenderersPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3BCD05ED-97E1-46DF-8034-533C84685EA2}");}
  }

  /// <summary>Registers or unregisters a class to the RasterConversionOp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterConversionOp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterConversionOp : CatReg
  {

    /// <summary>Registers a class to the RasterConversionOp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CD568B5A-CA31-11D2-9F3C-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the RasterConversionOp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CD568B5A-CA31-11D2-9F3C-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the RasterDataExclusionPropSheet component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterDataExclusionPropSheet class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterDataExclusionPropSheet : CatReg
  {

    /// <summary>Registers a class to the RasterDataExclusionPropSheet component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9A90E0A4-6265-11D3-9FD1-00C04F68E699}");}

    /// <summary>Unregisters a class from the RasterDataExclusionPropSheet component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9A90E0A4-6265-11D3-9FD1-00C04F68E699}");}
  }

  /// <summary>Registers or unregisters a class to the RasterDatasetLoadMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterDatasetLoadMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterDatasetLoadMenuCommands : CatReg
  {

    /// <summary>Registers a class to the RasterDatasetLoadMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A2C4C975-7BD6-45BF-81B2-F46F987CB7D1}");}

    /// <summary>Unregisters a class from the RasterDatasetLoadMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A2C4C975-7BD6-45BF-81B2-F46F987CB7D1}");}
  }

  /// <summary>Registers or unregisters a class to the RasterDatasetPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterDatasetPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterDatasetPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RasterDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{74F98CC2-E2E7-11D2-9F51-00C04F8ED21A}");}

    /// <summary>Unregisters a class from the RasterDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{74F98CC2-E2E7-11D2-9F51-00C04F8ED21A}");}
  }

  /// <summary>Registers or unregisters a class to the RasterExportMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterExportMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterExportMenuCommands : CatReg
  {

    /// <summary>Registers a class to the RasterExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{837FAC81-38C9-11D4-8D94-00C04F5B87B2}");}

    /// <summary>Unregisters a class from the RasterExportMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{837FAC81-38C9-11D4-8D94-00C04F5B87B2}");}
  }

  /// <summary>Registers or unregisters a class to the RasterFunctionPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterFunctionPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterFunctionPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RasterFunctionPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8762A26F-B68F-4E97-93AA-F4C402538ACE}");}

    /// <summary>Unregisters a class from the RasterFunctionPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8762A26F-B68F-4E97-93AA-F4C402538ACE}");}
  }

  /// <summary>Registers or unregisters a class to the RasterFunctions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterFunctions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterFunctions : CatReg
  {

    /// <summary>Registers a class to the RasterFunctions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{01D1412F-EB0F-4CFB-B9E5-F248BE838131}");}

    /// <summary>Unregisters a class from the RasterFunctions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{01D1412F-EB0F-4CFB-B9E5-F248BE838131}");}
  }

  /// <summary>Registers or unregisters a class to the RasterGxExportFilters component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterGxExportFilters class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterGxExportFilters : CatReg
  {

    /// <summary>Registers a class to the RasterGxExportFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8837B6E0-7F9E-11D4-B284-00508BCDC7C8}");}

    /// <summary>Unregisters a class from the RasterGxExportFilters component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8837B6E0-7F9E-11D4-B284-00508BCDC7C8}");}
  }

  /// <summary>Registers or unregisters a class to the RasterLayerDataMenuItems component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterLayerDataMenuItems class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterLayerDataMenuItems : CatReg
  {

    /// <summary>Registers a class to the RasterLayerDataMenuItems component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{137D296C-A38F-42DC-A4EC-964B6FD7995E}");}

    /// <summary>Unregisters a class from the RasterLayerDataMenuItems component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{137D296C-A38F-42DC-A4EC-964B6FD7995E}");}
  }

  /// <summary>Registers or unregisters a class to the RasterLayerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterLayerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterLayerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RasterLayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2AD25BF1-3C02-11D3-A3FA-0004AC1B1D86}");}

    /// <summary>Unregisters a class from the RasterLayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2AD25BF1-3C02-11D3-A3FA-0004AC1B1D86}");}
  }

  /// <summary>Registers or unregisters a class to the RasterRendererMakers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterRendererMakers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterRendererMakers : CatReg
  {

    /// <summary>Registers a class to the RasterRendererMakers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F38F6DB0-C73E-11D4-B290-00508BCDC7C8}");}

    /// <summary>Unregisters a class from the RasterRendererMakers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F38F6DB0-C73E-11D4-B290-00508BCDC7C8}");}
  }

  /// <summary>Registers or unregisters a class to the RasterRenderers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterRenderers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterRenderers : CatReg
  {

    /// <summary>Registers a class to the RasterRenderers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7F529451-4743-4C4B-94B4-8140A9C2B4D4}");}

    /// <summary>Unregisters a class from the RasterRenderers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7F529451-4743-4C4B-94B4-8140A9C2B4D4}");}
  }

  /// <summary>Registers or unregisters a class to the RasterSensorInfoPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterSensorInfoPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterSensorInfoPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RasterSensorInfoPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A3E70CBD-C390-459D-9885-84C184C1C4B0}");}

    /// <summary>Unregisters a class from the RasterSensorInfoPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A3E70CBD-C390-459D-9885-84C184C1C4B0}");}
  }

  /// <summary>Registers or unregisters a class to the RasterSnappingPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterSnappingPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterSnappingPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RasterSnappingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{03013C0E-CC51-4247-A90D-0621B508E55F}");}

    /// <summary>Unregisters a class from the RasterSnappingPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{03013C0E-CC51-4247-A90D-0621B508E55F}");}
  }

  /// <summary>Registers or unregisters a class to the RasterStatEnvDialog component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterStatEnvDialog class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterStatEnvDialog : CatReg
  {

    /// <summary>Registers a class to the RasterStatEnvDialog component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{80F65394-FD12-11D2-9F63-00C04F68E699}");}

    /// <summary>Unregisters a class from the RasterStatEnvDialog component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{80F65394-FD12-11D2-9F63-00C04F68E699}");}
  }

  /// <summary>Registers or unregisters a class to the RasterTransformationOp component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterTransformationOp class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterTransformationOp : CatReg
  {

    /// <summary>Registers a class to the RasterTransformationOp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EB3F5D30-1306-11D3-9F45-00C04F8ED1D7}");}

    /// <summary>Unregisters a class from the RasterTransformationOp component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EB3F5D30-1306-11D3-9F45-00C04F8ED1D7}");}
  }

  /// <summary>Registers or unregisters a class to the RasterTypeFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterTypeFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterTypeFactory : CatReg
  {

    /// <summary>Registers a class to the RasterTypeFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AF8A03D8-A6F1-4A56-B79B-6B157F69C08B}");}

    /// <summary>Unregisters a class from the RasterTypeFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AF8A03D8-A6F1-4A56-B79B-6B157F69C08B}");}
  }

  /// <summary>Registers or unregisters a class to the RasterTypePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RasterTypePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RasterTypePropertyPages : CatReg
  {

    /// <summary>Registers a class to the RasterTypePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A8583828-7520-4B6E-83AA-E0EF7093D2DA}");}

    /// <summary>Unregisters a class from the RasterTypePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A8583828-7520-4B6E-83AA-E0EF7093D2DA}");}
  }

  /// <summary>Registers or unregisters a class to the RelationshipClassPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RelationshipClassPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RelationshipClassPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RelationshipClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{05318B65-DE31-11D2-9F54-00C04F6BC626}");}

    /// <summary>Unregisters a class from the RelationshipClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{05318B65-DE31-11D2-9F54-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the RendererPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RendererPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RendererPropertyPages : CatReg
  {

    /// <summary>Registers a class to the RendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{962BD9A9-1EC8-11D3-9F4D-00C04F6BC709}");}

    /// <summary>Unregisters a class from the RendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{962BD9A9-1EC8-11D3-9F4D-00C04F6BC709}");}
  }

  /// <summary>Registers or unregisters a class to the RepresentationClassPropertyPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RepresentationClassPropertyPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RepresentationClassPropertyPage : CatReg
  {

    /// <summary>Registers a class to the RepresentationClassPropertyPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7E2AFAC6-D6D3-450D-B485-DA47A1921E67}");}

    /// <summary>Unregisters a class from the RepresentationClassPropertyPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7E2AFAC6-D6D3-450D-B485-DA47A1921E67}");}
  }

  /// <summary>Registers or unregisters a class to the RuntimeSupported3DTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RuntimeSupported3DTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RuntimeSupported3DTools : CatReg
  {

    /// <summary>Registers a class to the RuntimeSupported3DTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7A5F28EE-D9BA-467D-8B82-34FC8008F826}");}

    /// <summary>Unregisters a class from the RuntimeSupported3DTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7A5F28EE-D9BA-467D-8B82-34FC8008F826}");}
  }

  /// <summary>Registers or unregisters a class to the RuntimeSupportedAdvancedTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RuntimeSupportedAdvancedTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RuntimeSupportedAdvancedTools : CatReg
  {

    /// <summary>Registers a class to the RuntimeSupportedAdvancedTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0A2AD811-7215-4A95-92F3-9C29DE502E9B}");}

    /// <summary>Unregisters a class from the RuntimeSupportedAdvancedTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0A2AD811-7215-4A95-92F3-9C29DE502E9B}");}
  }

  /// <summary>Registers or unregisters a class to the RuntimeSupportedNetworkAnalystTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RuntimeSupportedNetworkAnalystTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RuntimeSupportedNetworkAnalystTools : CatReg
  {

    /// <summary>Registers a class to the RuntimeSupportedNetworkAnalystTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AE2DFB1C-BB14-4852-8CE5-3930E530EABA}");}

    /// <summary>Unregisters a class from the RuntimeSupportedNetworkAnalystTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AE2DFB1C-BB14-4852-8CE5-3930E530EABA}");}
  }

  /// <summary>Registers or unregisters a class to the RuntimeSupportedSpatialAnalystTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RuntimeSupportedSpatialAnalystTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RuntimeSupportedSpatialAnalystTools : CatReg
  {

    /// <summary>Registers a class to the RuntimeSupportedSpatialAnalystTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{668A8D25-AF4A-468F-9750-ADFB75783AB9}");}

    /// <summary>Unregisters a class from the RuntimeSupportedSpatialAnalystTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{668A8D25-AF4A-468F-9750-ADFB75783AB9}");}
  }

  /// <summary>Registers or unregisters a class to the RuntimeSupportedStandardTools component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the RuntimeSupportedStandardTools class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class RuntimeSupportedStandardTools : CatReg
  {

    /// <summary>Registers a class to the RuntimeSupportedStandardTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{29F0DF2A-0BFD-49BE-90CF-5E74F3AAE8D5}");}

    /// <summary>Unregisters a class from the RuntimeSupportedStandardTools component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{29F0DF2A-0BFD-49BE-90CF-5E74F3AAE8D5}");}
  }

  /// <summary>Registers or unregisters a class to the SAOperation component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SAOperation class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SAOperation : CatReg
  {

    /// <summary>Registers a class to the SAOperation component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{FAF0CFBB-CD00-11D3-A051-00C04F68E699}");}

    /// <summary>Unregisters a class from the SAOperation component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{FAF0CFBB-CD00-11D3-A051-00C04F68E699}");}
  }

  /// <summary>Registers or unregisters a class to the ScaleBars component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ScaleBars class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ScaleBars : CatReg
  {

    /// <summary>Registers a class to the ScaleBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{34DC96D1-186D-11D3-B8A3-00600802E603}");}

    /// <summary>Unregisters a class from the ScaleBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{34DC96D1-186D-11D3-B8A3-00600802E603}");}
  }

  /// <summary>Registers or unregisters a class to the SceneExporter3dDrivers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SceneExporter3dDrivers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SceneExporter3dDrivers : CatReg
  {

    /// <summary>Registers a class to the SceneExporter3dDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D6AC48F8-37F4-11D4-A168-444553547777}");}

    /// <summary>Unregisters a class from the SceneExporter3dDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D6AC48F8-37F4-11D4-A168-444553547777}");}
  }

  /// <summary>Registers or unregisters a class to the SceneExporter3dPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SceneExporter3dPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SceneExporter3dPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SceneExporter3dPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D6AC48FC-37F4-11D4-A168-444553547777}");}

    /// <summary>Unregisters a class from the SceneExporter3dPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D6AC48FC-37F4-11D4-A168-444553547777}");}
  }

  /// <summary>Registers or unregisters a class to the SceneExporterVideoDrivers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SceneExporterVideoDrivers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SceneExporterVideoDrivers : CatReg
  {

    /// <summary>Registers a class to the SceneExporterVideoDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4251BA09-9106-11D5-B29F-00508BCDDE28}");}

    /// <summary>Unregisters a class from the SceneExporterVideoDrivers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4251BA09-9106-11D5-B29F-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the SceneExporterVideoPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SceneExporterVideoPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SceneExporterVideoPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SceneExporterVideoPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4251BA0A-9106-11D5-B29F-00508BCDDE28}");}

    /// <summary>Unregisters a class from the SceneExporterVideoPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4251BA0A-9106-11D5-B29F-00508BCDDE28}");}
  }

  /// <summary>Registers or unregisters a class to the ScenePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ScenePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ScenePropertyPages : CatReg
  {

    /// <summary>Registers a class to the ScenePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CF228351-10A9-11D4-9F7F-00C04F6BC619}");}

    /// <summary>Unregisters a class from the ScenePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CF228351-10A9-11D4-9F7F-00C04F6BC619}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicAlgorithmPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicAlgorithmPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicAlgorithmPages : CatReg
  {

    /// <summary>Registers a class to the SchematicAlgorithmPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F1C0AFCB-F506-4F25-91B9-23B9D2A1360A}");}

    /// <summary>Unregisters a class from the SchematicAlgorithmPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F1C0AFCB-F506-4F25-91B9-23B9D2A1360A}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicAlgorithms component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicAlgorithms class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicAlgorithms : CatReg
  {

    /// <summary>Registers a class to the SchematicAlgorithms component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9443C4F2-4838-4FAB-999B-AE12ED2FE7D3}");}

    /// <summary>Unregisters a class from the SchematicAlgorithms component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9443C4F2-4838-4FAB-999B-AE12ED2FE7D3}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicAnalystPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicAnalystPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicAnalystPages : CatReg
  {

    /// <summary>Registers a class to the SchematicAnalystPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{437DC6A3-81DA-4E02-A546-23023BD9A090}");}

    /// <summary>Unregisters a class from the SchematicAnalystPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{437DC6A3-81DA-4E02-A546-23023BD9A090}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicAnalysts component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicAnalysts class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicAnalysts : CatReg
  {

    /// <summary>Registers a class to the SchematicAnalysts component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F95EF350-3523-4D38-9BF7-D3990189B98C}");}

    /// <summary>Unregisters a class from the SchematicAnalysts component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F95EF350-3523-4D38-9BF7-D3990189B98C}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicBuilderEngine component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicBuilderEngine class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicBuilderEngine : CatReg
  {

    /// <summary>Registers a class to the SchematicBuilderEngine component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7C4AED2-AD49-45A6-874D-80124D6105D9}");}

    /// <summary>Unregisters a class from the SchematicBuilderEngine component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7C4AED2-AD49-45A6-874D-80124D6105D9}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicBuilderPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicBuilderPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicBuilderPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SchematicBuilderPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8877568E-4C6F-4F54-8035-7C1E0162BC92}");}

    /// <summary>Unregisters a class from the SchematicBuilderPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8877568E-4C6F-4F54-8035-7C1E0162BC92}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicBuilders component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicBuilders class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicBuilders : CatReg
  {

    /// <summary>Registers a class to the SchematicBuilders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E1C4348E-3FCD-4FB6-B80A-875D13259D8F}");}

    /// <summary>Unregisters a class from the SchematicBuilders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E1C4348E-3FCD-4FB6-B80A-875D13259D8F}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicBuilderUI component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicBuilderUI class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicBuilderUI : CatReg
  {

    /// <summary>Registers a class to the SchematicBuilderUI component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3DD691AF-9F04-498C-9470-484679B343B6}");}

    /// <summary>Unregisters a class from the SchematicBuilderUI component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3DD691AF-9F04-498C-9470-484679B343B6}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicCreateDiagramDialog component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicCreateDiagramDialog class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicCreateDiagramDialog : CatReg
  {

    /// <summary>Registers a class to the SchematicCreateDiagramDialog component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3CEEA4C3-3E09-4867-9BA3-CC6482D7F186}");}

    /// <summary>Unregisters a class from the SchematicCreateDiagramDialog component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3CEEA4C3-3E09-4867-9BA3-CC6482D7F186}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicDatasetPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicDatasetPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicDatasetPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SchematicDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{344C293D-545A-4B83-8B55-BA10997C3E49}");}

    /// <summary>Unregisters a class from the SchematicDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{344C293D-545A-4B83-8B55-BA10997C3E49}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicDiagramPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicDiagramPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicDiagramPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SchematicDiagramPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{8BE0C151-4BEE-45BF-8E98-76FD48B8FAF9}");}

    /// <summary>Unregisters a class from the SchematicDiagramPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{8BE0C151-4BEE-45BF-8E98-76FD48B8FAF9}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicEditingOptionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicEditingOptionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicEditingOptionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SchematicEditingOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{ED59A387-C431-4F45-938F-E7930E20A735}");}

    /// <summary>Unregisters a class from the SchematicEditingOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{ED59A387-C431-4F45-938F-E7930E20A735}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicFolderPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicFolderPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicFolderPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SchematicFolderPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3833B834-3D58-4727-B395-07F83D615119}");}

    /// <summary>Unregisters a class from the SchematicFolderPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3833B834-3D58-4727-B395-07F83D615119}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicOptionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicOptionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicOptionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SchematicOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2EB82C6E-B130-43EA-9444-7262237D2615}");}

    /// <summary>Unregisters a class from the SchematicOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2EB82C6E-B130-43EA-9444-7262237D2615}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicRelationManagers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicRelationManagers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicRelationManagers : CatReg
  {

    /// <summary>Registers a class to the SchematicRelationManagers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{98DD81D0-2AFD-4246-AC8D-5CCD261C72CF}");}

    /// <summary>Unregisters a class from the SchematicRelationManagers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{98DD81D0-2AFD-4246-AC8D-5CCD261C72CF}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicRulePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicRulePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicRulePropertyPages : CatReg
  {

    /// <summary>Registers a class to the SchematicRulePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AF04CE4A-FF08-43EB-9FB7-4A25452EFA53}");}

    /// <summary>Unregisters a class from the SchematicRulePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AF04CE4A-FF08-43EB-9FB7-4A25452EFA53}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicRules component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicRules class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicRules : CatReg
  {

    /// <summary>Registers a class to the SchematicRules component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A5005F0F-7FB8-40C1-84D9-22323E1225EE}");}

    /// <summary>Unregisters a class from the SchematicRules component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A5005F0F-7FB8-40C1-84D9-22323E1225EE}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicRulesExtendedCriteria component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicRulesExtendedCriteria class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicRulesExtendedCriteria : CatReg
  {

    /// <summary>Registers a class to the SchematicRulesExtendedCriteria component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AD8CEDB7-A1F8-427A-B598-23FACDF8116C}");}

    /// <summary>Unregisters a class from the SchematicRulesExtendedCriteria component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AD8CEDB7-A1F8-427A-B598-23FACDF8116C}");}
  }

  /// <summary>Registers or unregisters a class to the SchematicToolsEdit component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SchematicToolsEdit class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SchematicToolsEdit : CatReg
  {

    /// <summary>Registers a class to the SchematicToolsEdit component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EEBAAE14-3DC1-41EE-A369-10F23C931254}");}

    /// <summary>Unregisters a class from the SchematicToolsEdit component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EEBAAE14-3DC1-41EE-A369-10F23C931254}");}
  }

  /// <summary>Registers or unregisters a class to the SDSServerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SDSServerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SDSServerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SDSServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BF69ADC3-0F9D-4536-A581-A1D6AB2336F0}");}

    /// <summary>Unregisters a class from the SDSServerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BF69ADC3-0F9D-4536-A581-A1D6AB2336F0}");}
  }

  /// <summary>Registers or unregisters a class to the SearchResultsContextMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SearchResultsContextMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SearchResultsContextMenuCommands : CatReg
  {

    /// <summary>Registers a class to the SearchResultsContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{13A17004-CA63-46D3-B8CF-031F4C186B3C}");}

    /// <summary>Unregisters a class from the SearchResultsContextMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{13A17004-CA63-46D3-B8CF-031F4C186B3C}");}
  }

  /// <summary>Registers or unregisters a class to the ServerObjectDescriptions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ServerObjectDescriptions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ServerObjectDescriptions : CatReg
  {

    /// <summary>Registers a class to the ServerObjectDescriptions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{7B614D6C-647C-409E-B17F-72FD06546CD8}");}

    /// <summary>Unregisters a class from the ServerObjectDescriptions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{7B614D6C-647C-409E-B17F-72FD06546CD8}");}
  }

  /// <summary>Registers or unregisters a class to the Shadows component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the Shadows class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class Shadows : CatReg
  {

    /// <summary>Registers a class to the Shadows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4DE36362-E872-4159-B2DB-3ECEA4F57F0E}");}

    /// <summary>Unregisters a class from the Shadows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4DE36362-E872-4159-B2DB-3ECEA4F57F0E}");}
  }

  /// <summary>Registers or unregisters a class to the ShapeConstructorCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ShapeConstructorCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ShapeConstructorCommands : CatReg
  {

    /// <summary>Registers a class to the ShapeConstructorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{72C35B93-5E27-423E-8C4D-AFC2D35B22F1}");}

    /// <summary>Unregisters a class from the ShapeConstructorCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{72C35B93-5E27-423E-8C4D-AFC2D35B22F1}");}
  }

  /// <summary>Registers or unregisters a class to the ShapefileFeatureClassPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ShapefileFeatureClassPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ShapefileFeatureClassPropertyPages : CatReg
  {

    /// <summary>Registers a class to the ShapefileFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E10D6EC4-06E6-11D3-9F87-00C04F6BC626}");}

    /// <summary>Unregisters a class from the ShapefileFeatureClassPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E10D6EC4-06E6-11D3-9F87-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the ShapefileTablePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the ShapefileTablePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class ShapefileTablePropertyPages : CatReg
  {

    /// <summary>Registers a class to the ShapefileTablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E10D6EC5-06E6-11D3-9F87-00C04F6BC626}");}

    /// <summary>Unregisters a class from the ShapefileTablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E10D6EC5-06E6-11D3-9F87-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the SketchMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SketchMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SketchMenuCommands : CatReg
  {

    /// <summary>Registers a class to the SketchMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3DD0D4DD-01E6-41AC-BB50-108D11C763A7}");}

    /// <summary>Unregisters a class from the SketchMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3DD0D4DD-01E6-41AC-BB50-108D11C763A7}");}
  }

  /// <summary>Registers or unregisters a class to the SketchToolMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SketchToolMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SketchToolMenuCommands : CatReg
  {

    /// <summary>Registers a class to the SketchToolMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3DD0D4DC-01E6-41AC-BB50-108D11C763A7}");}

    /// <summary>Unregisters a class from the SketchToolMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3DD0D4DC-01E6-41AC-BB50-108D11C763A7}");}
  }

  /// <summary>Registers or unregisters a class to the SketchToolPaletteCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SketchToolPaletteCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SketchToolPaletteCommands : CatReg
  {

    /// <summary>Registers a class to the SketchToolPaletteCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{4F932E6B-2BD6-41E2-B41F-2FE4FF508109}");}

    /// <summary>Unregisters a class from the SketchToolPaletteCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{4F932E6B-2BD6-41E2-B41F-2FE4FF508109}");}
  }

  /// <summary>Registers or unregisters a class to the SMFinders component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SMFinders class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SMFinders : CatReg
  {

    /// <summary>Registers a class to the SMFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{EF3B2EBD-B87D-4B8D-AD63-DE1F2C4B73C8}");}

    /// <summary>Unregisters a class from the SMFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{EF3B2EBD-B87D-4B8D-AD63-DE1F2C4B73C8}");}
  }

  /// <summary>Registers or unregisters a class to the SnapAgents component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SnapAgents class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SnapAgents : CatReg
  {

    /// <summary>Registers a class to the SnapAgents component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5844F9F6-DC03-11D2-9F26-00C04F6BC979}");}

    /// <summary>Unregisters a class from the SnapAgents component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5844F9F6-DC03-11D2-9F26-00C04F6BC979}");}
  }

  /// <summary>Registers or unregisters a class to the StandaloneTablePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the StandaloneTablePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class StandaloneTablePropertyPages : CatReg
  {

    /// <summary>Registers a class to the StandaloneTablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DA7C157D-E58B-11D3-ADEA-00C04FA33A15}");}

    /// <summary>Unregisters a class from the StandaloneTablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DA7C157D-E58B-11D3-ADEA-00C04FA33A15}");}
  }

  /// <summary>Registers or unregisters a class to the StyleGalleryClasses component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the StyleGalleryClasses class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class StyleGalleryClasses : CatReg
  {

    /// <summary>Registers a class to the StyleGalleryClasses component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AC0E982B-91CB-11D1-8813-080009EC732A}");}

    /// <summary>Unregisters a class from the StyleGalleryClasses component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AC0E982B-91CB-11D1-8813-080009EC732A}");}
  }

  /// <summary>Registers or unregisters a class to the StyleImporter component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the StyleImporter class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class StyleImporter : CatReg
  {

    /// <summary>Registers a class to the StyleImporter component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{17049F82-8E15-11D2-983E-0080C7E04196}");}

    /// <summary>Unregisters a class from the StyleImporter component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{17049F82-8E15-11D2-983E-0080C7E04196}");}
  }

  /// <summary>Registers or unregisters a class to the StylePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the StylePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class StylePropertyPages : CatReg
  {

    /// <summary>Registers a class to the StylePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B6DD2405-29D6-11D3-B8AD-00600802E603}");}

    /// <summary>Unregisters a class from the StylePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B6DD2405-29D6-11D3-B8AD-00600802E603}");}
  }

  /// <summary>Registers or unregisters a class to the SxCommandBars component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxCommandBars class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxCommandBars : CatReg
  {

    /// <summary>Registers a class to the SxCommandBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F27D8291-A383-11D3-8206-0080C7597E71}");}

    /// <summary>Unregisters a class from the SxCommandBars component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F27D8291-A383-11D3-8206-0080C7597E71}");}
  }

  /// <summary>Registers or unregisters a class to the SxCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxCommands : CatReg
  {

    /// <summary>Registers a class to the SxCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F27D8292-A383-11D3-8206-0080C7597E71}");}

    /// <summary>Unregisters a class from the SxCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F27D8292-A383-11D3-8206-0080C7597E71}");}
  }

  /// <summary>Registers or unregisters a class to the SxContentsViews component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxContentsViews class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxContentsViews : CatReg
  {

    /// <summary>Registers a class to the SxContentsViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{BB07DB51-E57B-11D3-9F74-00C04F6BC619}");}

    /// <summary>Unregisters a class from the SxContentsViews component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{BB07DB51-E57B-11D3-9F74-00C04F6BC619}");}
  }

  /// <summary>Registers or unregisters a class to the SxContextAnalyzers component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxContextAnalyzers class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxContextAnalyzers : CatReg
  {

    /// <summary>Registers a class to the SxContextAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3BB42A1D-05A0-11D4-9F79-00C04F6BC619}");}

    /// <summary>Unregisters a class from the SxContextAnalyzers component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3BB42A1D-05A0-11D4-9F79-00C04F6BC619}");}
  }

  /// <summary>Registers or unregisters a class to the SxDockableWindows component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxDockableWindows class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxDockableWindows : CatReg
  {

    /// <summary>Registers a class to the SxDockableWindows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B9789374-FADC-11D3-A67F-0008C7DF97B9}");}

    /// <summary>Unregisters a class from the SxDockableWindows component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B9789374-FADC-11D3-A67F-0008C7DF97B9}");}
  }

  /// <summary>Registers or unregisters a class to the SxExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxExtensions : CatReg
  {

    /// <summary>Registers a class to the SxExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{369448D7-A6BD-11D3-ABB8-0008C73FCA1C}");}

    /// <summary>Unregisters a class from the SxExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{369448D7-A6BD-11D3-ABB8-0008C73FCA1C}");}
  }

  /// <summary>Registers or unregisters a class to the SxExtensionsJIT component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxExtensionsJIT class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxExtensionsJIT : CatReg
  {

    /// <summary>Registers a class to the SxExtensionsJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{836D800D-71B7-489E-A2F8-AEE3D77B06D7}");}

    /// <summary>Unregisters a class from the SxExtensionsJIT component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{836D800D-71B7-489E-A2F8-AEE3D77B06D7}");}
  }

  /// <summary>Registers or unregisters a class to the SxFinders component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxFinders class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxFinders : CatReg
  {

    /// <summary>Registers a class to the SxFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{B3E00B2A-25D3-11D4-A383-00C04F6BC619}");}

    /// <summary>Unregisters a class from the SxFinders component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{B3E00B2A-25D3-11D4-A383-00C04F6BC619}");}
  }

  /// <summary>Registers or unregisters a class to the SxGraphicPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxGraphicPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxGraphicPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SxGraphicPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A9521B7F-1F1E-11D6-A12D-00508BD60CB9}");}

    /// <summary>Unregisters a class from the SxGraphicPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A9521B7F-1F1E-11D6-A12D-00508BD60CB9}");}
  }

  /// <summary>Registers or unregisters a class to the SxImport3DFile component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxImport3DFile class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxImport3DFile : CatReg
  {

    /// <summary>Registers a class to the SxImport3DFile component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{980BC11D-BE90-4837-8123-18BCEC4D2096}");}

    /// <summary>Unregisters a class from the SxImport3DFile component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{980BC11D-BE90-4837-8123-18BCEC4D2096}");}
  }

  /// <summary>Registers or unregisters a class to the SxLayerPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxLayerPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxLayerPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SxLayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{3F82C99B-1C5F-11D4-A381-00C04F6BC619}");}

    /// <summary>Unregisters a class from the SxLayerPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{3F82C99B-1C5F-11D4-A381-00C04F6BC619}");}
  }

  /// <summary>Registers or unregisters a class to the SxOptionsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxOptionsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxOptionsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SxOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F58B83FF-31AE-11D4-A385-00C04F6BC619}");}

    /// <summary>Unregisters a class from the SxOptionsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F58B83FF-31AE-11D4-A385-00C04F6BC619}");}
  }

  /// <summary>Registers or unregisters a class to the SxPalettes component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxPalettes class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxPalettes : CatReg
  {

    /// <summary>Registers a class to the SxPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A51B87D1-A383-11D3-8206-0080C7597E71}");}

    /// <summary>Unregisters a class from the SxPalettes component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A51B87D1-A383-11D3-8206-0080C7597E71}");}
  }

  /// <summary>Registers or unregisters a class to the SxPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SxPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SxPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SxPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{779E31F8-25E1-11D4-9B80-00C04FA33299}");}

    /// <summary>Unregisters a class from the SxPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{779E31F8-25E1-11D4-9B80-00C04FA33299}");}
  }

  /// <summary>Registers or unregisters a class to the SymbolPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the SymbolPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class SymbolPropertyPages : CatReg
  {

    /// <summary>Registers a class to the SymbolPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{818B37C0-F34E-11D2-BC8F-0080C7E04196}");}

    /// <summary>Unregisters a class from the SymbolPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{818B37C0-F34E-11D2-BC8F-0080C7E04196}");}
  }

  /// <summary>Registers or unregisters a class to the TableFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TableFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TableFactory : CatReg
  {

    /// <summary>Registers a class to the TableFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2D264034-4A12-440C-A00D-8C229AACD2E7}");}

    /// <summary>Unregisters a class from the TableFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2D264034-4A12-440C-A00D-8C229AACD2E7}");}
  }

  /// <summary>Registers or unregisters a class to the TablePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TablePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TablePropertyPages : CatReg
  {

    /// <summary>Registers a class to the TablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{750D818D-E0B5-11D2-99BF-0000F80372B4}");}

    /// <summary>Unregisters a class from the TablePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{750D818D-E0B5-11D2-99BF-0000F80372B4}");}
  }

  /// <summary>Registers or unregisters a class to the TableWindowPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TableWindowPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TableWindowPropertyPages : CatReg
  {

    /// <summary>Registers a class to the TableWindowPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{DA51F911-EA46-4E57-9B9E-2CF443D34CAB}");}

    /// <summary>Unregisters a class from the TableWindowPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{DA51F911-EA46-4E57-9B9E-2CF443D34CAB}");}
  }

  /// <summary>Registers or unregisters a class to the TerrainPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TerrainPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TerrainPropertyPages : CatReg
  {

    /// <summary>Registers a class to the TerrainPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{32DBF620-5D33-4CEB-90E5-5A884DED680B}");}

    /// <summary>Unregisters a class from the TerrainPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{32DBF620-5D33-4CEB-90E5-5A884DED680B}");}
  }

  /// <summary>Registers or unregisters a class to the TerrainRendererPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TerrainRendererPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TerrainRendererPropertyPages : CatReg
  {

    /// <summary>Registers a class to the TerrainRendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0F2D0B33-8ABE-44F5-86DA-B134E22B0BB5}");}

    /// <summary>Unregisters a class from the TerrainRendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0F2D0B33-8ABE-44F5-86DA-B134E22B0BB5}");}
  }

  /// <summary>Registers or unregisters a class to the TextBackground component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TextBackground class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TextBackground : CatReg
  {

    /// <summary>Registers a class to the TextBackground component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F8AEACE0-25D1-11D3-80DA-0080C79F0371}");}

    /// <summary>Unregisters a class from the TextBackground component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F8AEACE0-25D1-11D3-80DA-0080C79F0371}");}
  }

  /// <summary>Registers or unregisters a class to the TextBackgroundPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TextBackgroundPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TextBackgroundPropertyPages : CatReg
  {

    /// <summary>Registers a class to the TextBackgroundPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F1CAF8B0-25C3-11D3-80DA-0080C79F0371}");}

    /// <summary>Unregisters a class from the TextBackgroundPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F1CAF8B0-25C3-11D3-80DA-0080C79F0371}");}
  }

  /// <summary>Registers or unregisters a class to the TextFilePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TextFilePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TextFilePropertyPages : CatReg
  {

    /// <summary>Registers a class to the TextFilePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{090BE115-10AB-11D4-AE05-00C04FA33A15}");}

    /// <summary>Unregisters a class from the TextFilePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{090BE115-10AB-11D4-AE05-00C04FA33A15}");}
  }

  /// <summary>Registers or unregisters a class to the TextSymbol component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TextSymbol class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TextSymbol : CatReg
  {

    /// <summary>Registers a class to the TextSymbol component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5424FB03-5713-11D2-97E5-0080C7E04196}");}

    /// <summary>Unregisters a class from the TextSymbol component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5424FB03-5713-11D2-97E5-0080C7E04196}");}
  }

  /// <summary>Registers or unregisters a class to the TinDatasetPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TinDatasetPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TinDatasetPropertyPages : CatReg
  {

    /// <summary>Registers a class to the TinDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{2A3354C9-24E1-11D3-9F4C-00C04F6BC619}");}

    /// <summary>Unregisters a class from the TinDatasetPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{2A3354C9-24E1-11D3-9F4C-00C04F6BC619}");}
  }

  /// <summary>Registers or unregisters a class to the TinRendererPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TinRendererPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TinRendererPropertyPages : CatReg
  {

    /// <summary>Registers a class to the TinRendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{19283BDF-656F-11D3-9F57-00C04F6BC619}");}

    /// <summary>Unregisters a class from the TinRendererPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{19283BDF-656F-11D3-9F57-00C04F6BC619}");}
  }

  /// <summary>Registers or unregisters a class to the TopologyPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TopologyPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TopologyPropertyPages : CatReg
  {

    /// <summary>Registers a class to the TopologyPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0D74B021-D997-4CBD-9A35-F22DDFB29519}");}

    /// <summary>Unregisters a class from the TopologyPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0D74B021-D997-4CBD-9A35-F22DDFB29519}");}
  }

  /// <summary>Registers or unregisters a class to the TraceTasks component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TraceTasks class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TraceTasks : CatReg
  {

    /// <summary>Registers a class to the TraceTasks component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5BF495FA-95D1-11D2-AAEB-00C04FA37D59}");}

    /// <summary>Unregisters a class from the TraceTasks component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5BF495FA-95D1-11D2-AAEB-00C04FA37D59}");}
  }

  /// <summary>Registers or unregisters a class to the TRAFFIC_PROVIDER component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TRAFFIC_PROVIDER class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TRAFFIC_PROVIDER : CatReg
  {

    /// <summary>Registers a class to the TRAFFIC_PROVIDER component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{94BF94BE-9798-46A3-BA25-0BDA4FF3EF22}");}

    /// <summary>Unregisters a class from the TRAFFIC_PROVIDER component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{94BF94BE-9798-46A3-BA25-0BDA4FF3EF22}");}
  }

  /// <summary>Registers or unregisters a class to the TrainingMenuCommands component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TrainingMenuCommands class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TrainingMenuCommands : CatReg
  {

    /// <summary>Registers a class to the TrainingMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{651063DC-E6DC-4840-9246-98E6F27B2381}");}

    /// <summary>Unregisters a class from the TrainingMenuCommands component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{651063DC-E6DC-4840-9246-98E6F27B2381}");}
  }

  /// <summary>Registers or unregisters a class to the TransformationMethods component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the TransformationMethods class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class TransformationMethods : CatReg
  {

    /// <summary>Registers a class to the TransformationMethods component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{D9246646-BEDB-4D2B-88B0-5B94D1BBD5A7}");}

    /// <summary>Unregisters a class from the TransformationMethods component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{D9246646-BEDB-4D2B-88B0-5B94D1BBD5A7}");}
  }

  /// <summary>Registers or unregisters a class to the UtilityNetworkAnalysisGNPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the UtilityNetworkAnalysisGNPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class UtilityNetworkAnalysisGNPropertyPages : CatReg
  {

    /// <summary>Registers a class to the UtilityNetworkAnalysisGNPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{69BCACD9-019C-11D3-9F7D-00C04F6BDF0E}");}

    /// <summary>Unregisters a class from the UtilityNetworkAnalysisGNPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{69BCACD9-019C-11D3-9F7D-00C04F6BDF0E}");}
  }

  /// <summary>Registers or unregisters a class to the UtilityNetworkAnalysisPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the UtilityNetworkAnalysisPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class UtilityNetworkAnalysisPropertyPages : CatReg
  {

    /// <summary>Registers a class to the UtilityNetworkAnalysisPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{97499635-F279-11D2-9F6A-00C04F6BDF0E}");}

    /// <summary>Unregisters a class from the UtilityNetworkAnalysisPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{97499635-F279-11D2-9F6A-00C04F6BDF0E}");}
  }

  /// <summary>Registers or unregisters a class to the UtilityNetworkTasks component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the UtilityNetworkTasks class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class UtilityNetworkTasks : CatReg
  {

    /// <summary>Registers a class to the UtilityNetworkTasks component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{39DC1B4F-BE34-11D2-BABE-00C04FA33C20}");}

    /// <summary>Unregisters a class from the UtilityNetworkTasks component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{39DC1B4F-BE34-11D2-BABE-00C04FA33C20}");}
  }

  /// <summary>Registers or unregisters a class to the VectorizationPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the VectorizationPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class VectorizationPropertyPages : CatReg
  {

    /// <summary>Registers a class to the VectorizationPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CC36327A-FB36-4318-8E92-A6A41B8C2763}");}

    /// <summary>Unregisters a class from the VectorizationPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CC36327A-FB36-4318-8E92-A6A41B8C2763}");}
  }

  /// <summary>Registers or unregisters a class to the VersionPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the VersionPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class VersionPropertyPages : CatReg
  {

    /// <summary>Registers a class to the VersionPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0224F7BC-F736-11D2-9F2E-00C04F6BC979}");}

    /// <summary>Unregisters a class from the VersionPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0224F7BC-F736-11D2-9F2E-00C04F6BC979}");}
  }

  /// <summary>Registers or unregisters a class to the VerticalCoordSysPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the VerticalCoordSysPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class VerticalCoordSysPropertyPages : CatReg
  {

    /// <summary>Registers a class to the VerticalCoordSysPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{9D8F83A2-02DB-4464-8314-188C554ED6DC}");}

    /// <summary>Unregisters a class from the VerticalCoordSysPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{9D8F83A2-02DB-4464-8314-188C554ED6DC}");}
  }

  /// <summary>Registers or unregisters a class to the VideoExporterPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the VideoExporterPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class VideoExporterPropertyPages : CatReg
  {

    /// <summary>Registers a class to the VideoExporterPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{856A40CB-3D91-4B19-897C-9CF138E43529}");}

    /// <summary>Unregisters a class from the VideoExporterPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{856A40CB-3D91-4B19-897C-9CF138E43529}");}
  }

  /// <summary>Registers or unregisters a class to the WCSConnectionContextMenu component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WCSConnectionContextMenu class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WCSConnectionContextMenu : CatReg
  {

    /// <summary>Registers a class to the WCSConnectionContextMenu component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A2FC4D55-08B2-485B-AC47-C5C370942218}");}

    /// <summary>Unregisters a class from the WCSConnectionContextMenu component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A2FC4D55-08B2-485B-AC47-C5C370942218}");}
  }

  /// <summary>Registers or unregisters a class to the WCSConnectionPropertiesPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WCSConnectionPropertiesPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WCSConnectionPropertiesPage : CatReg
  {

    /// <summary>Registers a class to the WCSConnectionPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{E074D570-B784-43E7-8B57-A3737672CDF4}");}

    /// <summary>Unregisters a class from the WCSConnectionPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{E074D570-B784-43E7-8B57-A3737672CDF4}");}
  }

  /// <summary>Registers or unregisters a class to the WCSCoverageContextMenu component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WCSCoverageContextMenu class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WCSCoverageContextMenu : CatReg
  {

    /// <summary>Registers a class to the WCSCoverageContextMenu component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{0117DC8D-7FE7-403F-BF6A-F4722A391651}");}

    /// <summary>Unregisters a class from the WCSCoverageContextMenu component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{0117DC8D-7FE7-403F-BF6A-F4722A391651}");}
  }

  /// <summary>Registers or unregisters a class to the WCSDisconnectedConnectionPropertiesPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WCSDisconnectedConnectionPropertiesPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WCSDisconnectedConnectionPropertiesPage : CatReg
  {

    /// <summary>Registers a class to the WCSDisconnectedConnectionPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{CAA46CEC-2324-4968-A492-FEE997B3C7AF}");}

    /// <summary>Unregisters a class from the WCSDisconnectedConnectionPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{CAA46CEC-2324-4968-A492-FEE997B3C7AF}");}
  }

  /// <summary>Registers or unregisters a class to the WMSConnectionContextMenu component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WMSConnectionContextMenu class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WMSConnectionContextMenu : CatReg
  {

    /// <summary>Registers a class to the WMSConnectionContextMenu component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{A7E52477-92EF-4111-85F8-6A95860934B7}");}

    /// <summary>Unregisters a class from the WMSConnectionContextMenu component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{A7E52477-92EF-4111-85F8-6A95860934B7}");}
  }

  /// <summary>Registers or unregisters a class to the WMSConnectionPropertiesPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WMSConnectionPropertiesPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WMSConnectionPropertiesPage : CatReg
  {

    /// <summary>Registers a class to the WMSConnectionPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{AE0FAD19-7F6D-44F3-9AEA-F2EE7CA70E94}");}

    /// <summary>Unregisters a class from the WMSConnectionPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{AE0FAD19-7F6D-44F3-9AEA-F2EE7CA70E94}");}
  }

  /// <summary>Registers or unregisters a class to the WMSMapContextMenu component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WMSMapContextMenu class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WMSMapContextMenu : CatReg
  {

    /// <summary>Registers a class to the WMSMapContextMenu component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C58809CB-1F58-4E42-BD42-1DEE0741DF0C}");}

    /// <summary>Unregisters a class from the WMSMapContextMenu component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C58809CB-1F58-4E42-BD42-1DEE0741DF0C}");}
  }

  /// <summary>Registers or unregisters a class to the WMTSConnectionPropertiesPage component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WMTSConnectionPropertiesPage class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WMTSConnectionPropertiesPage : CatReg
  {

    /// <summary>Registers a class to the WMTSConnectionPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{5F0172E4-6772-45AF-8B61-B1B391A8E523}");}

    /// <summary>Unregisters a class from the WMTSConnectionPropertiesPage component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{5F0172E4-6772-45AF-8B61-B1B391A8E523}");}
  }

  /// <summary>Registers or unregisters a class to the WorkspaceDatasetExtensions component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WorkspaceDatasetExtensions class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WorkspaceDatasetExtensions : CatReg
  {

    /// <summary>Registers a class to the WorkspaceDatasetExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{F9196CDC-C3F2-4AE6-A1B2-6A364141E873}");}

    /// <summary>Unregisters a class from the WorkspaceDatasetExtensions component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{F9196CDC-C3F2-4AE6-A1B2-6A364141E873}");}
  }

  /// <summary>Registers or unregisters a class to the WorkspaceDomainsPropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WorkspaceDomainsPropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WorkspaceDomainsPropertyPages : CatReg
  {

    /// <summary>Registers a class to the WorkspaceDomainsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C255D347-CB5C-11D2-9F3C-00C04F6BC626}");}

    /// <summary>Unregisters a class from the WorkspaceDomainsPropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C255D347-CB5C-11D2-9F3C-00C04F6BC626}");}
  }

  /// <summary>Registers or unregisters a class to the WorkspaceFactory component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WorkspaceFactory class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WorkspaceFactory : CatReg
  {

    /// <summary>Registers a class to the WorkspaceFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{07BC056E-DB8A-11D1-AA81-00C04FA33A15}");}

    /// <summary>Unregisters a class from the WorkspaceFactory component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{07BC056E-DB8A-11D1-AA81-00C04FA33A15}");}
  }

  /// <summary>Registers or unregisters a class to the WorkspacePropertyPages component category.</summary>
#if _OBSOLETE_ATTRIBUTE
  [ObsoleteAttribute("Use of this type is no longer recommended because it is being deprecated.  Use instead the WorkspacePropertyPages class in the ESRI.ArcGIS.ADF.CATIDs namespace.", false)]
#endif
  public class WorkspacePropertyPages : CatReg
  {

    /// <summary>Registers a class to the WorkspacePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be registered.</param>
    public static void Register(String CLSID) {Reg(CLSID, "{C255D343-CB5C-11D2-9F3C-00C04F6BC626}");}

    /// <summary>Unregisters a class from the WorkspacePropertyPages component category.</summary>
    /// <param name="CLSID">The CLSID of the class to be unregistered.</param>
    public static void Unregister(String CLSID) {Unreg(CLSID, "{C255D343-CB5C-11D2-9F3C-00C04F6BC626}");}
  }
#else // _ARC_EXPLORER
#endif // _ARC_EXPLORER

}
