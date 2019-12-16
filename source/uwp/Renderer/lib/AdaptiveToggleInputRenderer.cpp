// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveToggleInput.h"
#include "AdaptiveToggleInputRenderer.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveToggleInputRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleInputRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                                _In_ IAdaptiveRenderContext* renderContext,
                                                _In_ IAdaptiveRenderArgs* renderArgs,
                                                _COM_Outptr_ IUIElement** toggleInputControl) noexcept
    try
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!XamlHelpers::SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Toggle Input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveToggleInput> adaptiveToggleInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveToggleInput));

        ComPtr<ICheckBox> checkBox =
            XamlHelpers::CreateXamlClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));

        HString title;
        RETURN_IF_FAILED(adaptiveToggleInput->get_Title(title.GetAddressOf()));

        boolean wrap;
        adaptiveToggleInput->get_Wrap(&wrap);

        XamlHelpers::SetContent(checkBox.Get(), title.Get(), wrap);

        HString value;
        RETURN_IF_FAILED(adaptiveToggleInput->get_Value(value.GetAddressOf()));

        HString valueOn;
        RETURN_IF_FAILED(adaptiveToggleInput->get_ValueOn(valueOn.GetAddressOf()));

        INT32 compareValueOn;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(value.Get(), valueOn.Get(), &compareValueOn));

        XamlHelpers::SetToggleValue(checkBox.Get(), (compareValueOn == 0));

        ComPtr<IUIElement> checkboxAsUIElement;
        RETURN_IF_FAILED(checkBox.As(&checkboxAsUIElement));
        RETURN_IF_FAILED(XamlHelpers::AddHandledTappedEvent(checkboxAsUIElement.Get()));

        ComPtr<IFrameworkElement> frameworkElement;
        RETURN_IF_FAILED(checkBox.As(&frameworkElement));
        RETURN_IF_FAILED(frameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
        RETURN_IF_FAILED(
            XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", frameworkElement.Get()));

        XamlHelpers::AddInputValueToContext(renderContext, adaptiveCardElement, *toggleInputControl);

        // Check if this toggle has a label. If so, add it to a stackPanel with the checkBox
        ComPtr<IAdaptiveInputElement> adaptiveToggleInputAsAdaptiveInput;
        RETURN_IF_FAILED(adaptiveToggleInput.As(&adaptiveToggleInputAsAdaptiveInput));

        ComPtr<IUIElement> labelControl;
        RETURN_IF_FAILED(XamlHelpers::RenderInputLabel(adaptiveToggleInputAsAdaptiveInput.Get(), renderContext, renderArgs, &labelControl));

        if (labelControl != nullptr)
        {
            ComPtr<IStackPanel> stackPanel =
                XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

            ComPtr<IPanel> panel;
            RETURN_IF_FAILED(stackPanel.As(&panel));

            XamlHelpers::AppendXamlElementToPanel(labelControl.Get(), panel.Get());
            XamlHelpers::AppendXamlElementToPanel(checkBox.Get(), panel.Get());

            RETURN_IF_FAILED(stackPanel.CopyTo(toggleInputControl));
        }
        else
        {
            RETURN_IF_FAILED(checkboxAsUIElement.CopyTo(toggleInputControl));
        }

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleInputRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveToggleInput, AdaptiveSharedNamespace::ToggleInput, AdaptiveSharedNamespace::ToggleInputParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
